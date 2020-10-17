/*
 * Copyright 2016 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ir/iteration.h"
#include "ir/load-utils.h"
#include "ir/utils.h"
#include "support/hash.h"
#include "support/small_vector.h"
#include "wasm-traversal.h"
#include "wasm.h"

namespace wasm {

// Given a stack of expressions, checks if the topmost is used as a result.
// For example, if the parent is a block and the node is before the last
// position, it is not used.
bool ExpressionAnalyzer::isResultUsed(ExpressionStack& stack, Function* func) {
  for (int i = int(stack.size()) - 2; i >= 0; i--) {
    auto* curr = stack[i];
    auto* above = stack[i + 1];
    // only if and block can drop values (pre-drop expression was added) FIXME
    if (curr->is<Block>()) {
      auto* block = curr->cast<Block>();
      for (size_t j = 0; j < block->list.size() - 1; j++) {
        if (block->list[j] == above) {
          return false;
        }
      }
      assert(block->list.back() == above);
      // continue down
    } else if (curr->is<If>()) {
      auto* iff = curr->cast<If>();
      if (above == iff->condition) {
        return true;
      }
      if (!iff->ifFalse) {
        return false;
      }
      assert(above == iff->ifTrue || above == iff->ifFalse);
      // continue down
    } else {
      if (curr->is<Drop>()) {
        return false;
      }
      return true; // all other node types use the result
    }
  }
  // The value might be used, so it depends on if the function returns
  return func->sig.results != Type::none;
}

// Checks if a value is dropped.
bool ExpressionAnalyzer::isResultDropped(ExpressionStack& stack) {
  for (int i = int(stack.size()) - 2; i >= 0; i--) {
    auto* curr = stack[i];
    auto* above = stack[i + 1];
    if (curr->is<Block>()) {
      auto* block = curr->cast<Block>();
      for (size_t j = 0; j < block->list.size() - 1; j++) {
        if (block->list[j] == above) {
          return false;
        }
      }
      assert(block->list.back() == above);
      // continue down
    } else if (curr->is<If>()) {
      auto* iff = curr->cast<If>();
      if (above == iff->condition) {
        return false;
      }
      if (!iff->ifFalse) {
        return false;
      }
      assert(above == iff->ifTrue || above == iff->ifFalse);
      // continue down
    } else {
      if (curr->is<Drop>()) {
        return true; // dropped
      }
      return false; // all other node types use the result
    }
  }
  return false;
}

//
// Allows visiting the immediate fields of the expression. This is
// useful for comparisons and hashing.
//
// The passed-in visitor object must implement:
//  * visitScopeName - a Name that represents a block or loop scope
//  * visitNonScopeName - a non-scope name
//  * visitInt - anything that has a short enumeration, including
//               opcodes, # of bytes in a load, bools, etc. - must be
//               guaranteed to fit in an int32 or less.
//  * visitLiteral - a Literal
//  * visitType - a Type
//  * visitIndex - an Index
//  * visitAddress - an Address
//

namespace {

template<typename T> void visitImmediates(Expression* curr, T& visitor) {
  struct ImmediateVisitor : public OverriddenVisitor<ImmediateVisitor> {
    T& visitor;

    ImmediateVisitor(Expression* curr, T& visitor) : visitor(visitor) {
      this->visit(curr);
    }

    void visitBlock(Block* curr) { visitor.visitScopeName(curr->name); }
    void visitIf(If* curr) {}
    void visitLoop(Loop* curr) { visitor.visitScopeName(curr->name); }
    void visitBreak(Break* curr) { visitor.visitScopeName(curr->name); }
    void visitSwitch(Switch* curr) {
      for (auto target : curr->targets) {
        visitor.visitScopeName(target);
      }
      visitor.visitScopeName(curr->default_);
    }
    void visitCall(Call* curr) {
      visitor.visitNonScopeName(curr->target);
      visitor.visitInt(curr->isReturn);
    }
    void visitCallIndirect(CallIndirect* curr) {
      visitor.visitInt(curr->sig.params.getID());
      visitor.visitInt(curr->sig.results.getID());
      visitor.visitInt(curr->isReturn);
    }
    void visitLocalGet(LocalGet* curr) { visitor.visitIndex(curr->index); }
    void visitLocalSet(LocalSet* curr) { visitor.visitIndex(curr->index); }
    void visitGlobalGet(GlobalGet* curr) {
      visitor.visitNonScopeName(curr->name);
    }
    void visitGlobalSet(GlobalSet* curr) {
      visitor.visitNonScopeName(curr->name);
    }
    void visitLoad(Load* curr) {
      visitor.visitInt(curr->bytes);
      if (curr->type != Type::unreachable &&
          curr->bytes < curr->type.getByteSize()) {
        visitor.visitInt(curr->signed_);
      }
      visitor.visitAddress(curr->offset);
      visitor.visitAddress(curr->align);
      visitor.visitInt(curr->isAtomic);
    }
    void visitStore(Store* curr) {
      visitor.visitInt(curr->bytes);
      visitor.visitAddress(curr->offset);
      visitor.visitAddress(curr->align);
      visitor.visitInt(curr->isAtomic);
      visitor.visitInt(curr->valueType.getID());
    }
    void visitAtomicRMW(AtomicRMW* curr) {
      visitor.visitInt(curr->op);
      visitor.visitInt(curr->bytes);
      visitor.visitAddress(curr->offset);
    }
    void visitAtomicCmpxchg(AtomicCmpxchg* curr) {
      visitor.visitInt(curr->bytes);
      visitor.visitAddress(curr->offset);
    }
    void visitAtomicWait(AtomicWait* curr) {
      visitor.visitAddress(curr->offset);
      visitor.visitType(curr->expectedType);
    }
    void visitAtomicNotify(AtomicNotify* curr) {
      visitor.visitAddress(curr->offset);
    }
    void visitAtomicFence(AtomicFence* curr) { visitor.visitInt(curr->order); }
    void visitSIMDExtract(SIMDExtract* curr) {
      visitor.visitInt(curr->op);
      visitor.visitInt(curr->index);
    }
    void visitSIMDReplace(SIMDReplace* curr) {
      visitor.visitInt(curr->op);
      visitor.visitInt(curr->index);
    }
    void visitSIMDShuffle(SIMDShuffle* curr) {
      for (auto x : curr->mask) {
        visitor.visitInt(x);
      }
    }
    void visitSIMDTernary(SIMDTernary* curr) { visitor.visitInt(curr->op); }
    void visitSIMDShift(SIMDShift* curr) { visitor.visitInt(curr->op); }
    void visitSIMDLoad(SIMDLoad* curr) {
      visitor.visitInt(curr->op);
      visitor.visitAddress(curr->offset);
      visitor.visitAddress(curr->align);
    }
    void visitMemoryInit(MemoryInit* curr) {
      visitor.visitIndex(curr->segment);
    }
    void visitDataDrop(DataDrop* curr) { visitor.visitIndex(curr->segment); }
    void visitMemoryCopy(MemoryCopy* curr) {}
    void visitMemoryFill(MemoryFill* curr) {}
    void visitConst(Const* curr) { visitor.visitLiteral(curr->value); }
    void visitUnary(Unary* curr) { visitor.visitInt(curr->op); }
    void visitBinary(Binary* curr) { visitor.visitInt(curr->op); }
    void visitSelect(Select* curr) {}
    void visitDrop(Drop* curr) {}
    void visitReturn(Return* curr) {}
    void visitMemorySize(MemorySize* curr) {}
    void visitMemoryGrow(MemoryGrow* curr) {}
    void visitRefNull(RefNull* curr) { visitor.visitType(curr->type); }
    void visitRefIsNull(RefIsNull* curr) {}
    void visitRefFunc(RefFunc* curr) { visitor.visitNonScopeName(curr->func); }
    void visitRefEq(RefEq* curr) {}
    void visitTry(Try* curr) {}
    void visitThrow(Throw* curr) { visitor.visitNonScopeName(curr->event); }
    void visitRethrow(Rethrow* curr) {}
    void visitBrOnExn(BrOnExn* curr) {
      visitor.visitScopeName(curr->name);
      visitor.visitNonScopeName(curr->event);
    }
    void visitNop(Nop* curr) {}
    void visitUnreachable(Unreachable* curr) {}
    void visitPop(Pop* curr) {}
    void visitTupleMake(TupleMake* curr) {}
    void visitTupleExtract(TupleExtract* curr) {
      visitor.visitIndex(curr->index);
    }
    void visitI31New(I31New* curr) {}
    void visitI31Get(I31Get* curr) { visitor.visitInt(curr->signed_); }
    void visitRefTest(RefTest* curr) {
      WASM_UNREACHABLE("TODO (gc): ref.test");
    }
    void visitRefCast(RefCast* curr) {
      WASM_UNREACHABLE("TODO (gc): ref.cast");
    }
    void visitBrOnCast(BrOnCast* curr) {
      WASM_UNREACHABLE("TODO (gc): br_on_cast");
    }
    void visitRttCanon(RttCanon* curr) {
      WASM_UNREACHABLE("TODO (gc): rtt.canon");
    }
    void visitRttSub(RttSub* curr) { WASM_UNREACHABLE("TODO (gc): rtt.sub"); }
    void visitStructNew(StructNew* curr) {
      WASM_UNREACHABLE("TODO (gc): struct.new");
    }
    void visitStructGet(StructGet* curr) {
      WASM_UNREACHABLE("TODO (gc): struct.get");
    }
    void visitStructSet(StructSet* curr) {
      WASM_UNREACHABLE("TODO (gc): struct.set");
    }
    void visitArrayNew(ArrayNew* curr) {
      WASM_UNREACHABLE("TODO (gc): array.new");
    }
    void visitArrayGet(ArrayGet* curr) {
      WASM_UNREACHABLE("TODO (gc): array.get");
    }
    void visitArraySet(ArraySet* curr) {
      WASM_UNREACHABLE("TODO (gc): array.set");
    }
    void visitArrayLen(ArrayLen* curr) {
      WASM_UNREACHABLE("TODO (gc): array.len");
    }
  } singleton(curr, visitor);
}

} // namespace

bool ExpressionAnalyzer::flexibleEqual(Expression* left,
                                       Expression* right,
                                       ExprComparer comparer) {
  struct Comparer {
    // for each name on the left, the corresponding name on the right
    std::map<Name, Name> rightNames;
    std::vector<Expression*> leftStack;
    std::vector<Expression*> rightStack;

    bool noteNames(Name left, Name right) {
      if (left.is() != right.is()) {
        return false;
      }
      if (left.is()) {
        assert(rightNames.find(left) == rightNames.end());
        rightNames[left] = right;
      }
      return true;
    }

    bool compare(Expression* left, Expression* right, ExprComparer comparer) {
      // The empty name is the same on both sides.
      rightNames[Name()] = Name();

      leftStack.push_back(left);
      rightStack.push_back(right);

      while (leftStack.size() > 0 && rightStack.size() > 0) {
        left = leftStack.back();
        leftStack.pop_back();
        right = rightStack.back();
        rightStack.pop_back();
        if (!left != !right) {
          return false;
        }
        if (!left) {
          continue;
        }
        if (comparer(left, right)) {
          continue; // comparison hook, before all the rest
        }
        // Do the actual comparison, updating the names and stacks accordingly.
        if (!compareNodes(left, right)) {
          return false;
        }
// TODO make sure return's optinal node is ok handled
      }
      if (leftStack.size() > 0 || rightStack.size() > 0) {
        return false;
      }
      return true;
    }

    bool compareNodes(Expression* left, Expression* right) {
      if (left->_id != right->_id) {
        return false;
      }
      switch (left->_id) {
        #include "compare-expressions.generated.h"
        default: WASM_UNREACHABLE("unknown expression");
      }
    }
  };

  return Comparer().compare(left, right, comparer);
}

// hash an expression, ignoring superficial details like specific internal names
size_t ExpressionAnalyzer::hash(Expression* curr) {
  struct Hasher {
    size_t digest = wasm::hash(0);

    Index internalCounter = 0;
    // for each internal name, its unique id
    std::map<Name, Index> internalNames;
    ExpressionStack stack;

    void noteScopeName(Name curr) {
      if (curr.is()) {
        internalNames[curr] = internalCounter++;
      }
    }

    Hasher(Expression* curr) {
      stack.push_back(curr);

      while (stack.size() > 0) {
        curr = stack.back();
        stack.pop_back();
        if (!curr) {
          continue;
        }
        rehash(digest, curr->_id);
        // we often don't need to hash the type, as it is tied to other values
        // we are hashing anyhow, but there are exceptions: for example, a
        // local.get's type is determined by the function, so if we are
        // hashing only expression fragments, then two from different
        // functions may turn out the same even if the type differs. Likewise,
        // if we hash between modules, then we need to take int account
        // call_imports type, etc. The simplest thing is just to hash the
        // type for all of them.
        rehash(digest, curr->type.getID());
        // Blocks and loops introduce scoping.
        if (auto* block = curr->dynCast<Block>()) {
          noteScopeName(block->name);
        } else if (auto* loop = curr->dynCast<Loop>()) {
          noteScopeName(loop->name);
        } else {
          // For all other nodes, compare their immediate values
          visitImmediates(curr, *this);
        }
        // Hash children
        Index counter = 0;
        for (auto* child : ChildIterator(curr)) {
          stack.push_back(child);
          counter++;
        }
        // Sometimes children are optional, e.g. return, so we must hash
        // their number as well.
        rehash(digest, counter);
      }
    }

    void visitScopeName(Name curr) {
      // Names are relative, we give the same hash for
      // (block $x (br $x))
      // (block $y (br $y))
      static_assert(sizeof(Index) == sizeof(int32_t),
                    "wasm64 will need changes here");
      assert(internalNames.find(curr) != internalNames.end());
      rehash(digest, internalNames[curr]);
    }
    void visitNonScopeName(Name curr) { rehash(digest, uint64_t(curr.str)); }
    void visitInt(int32_t curr) { rehash(digest, curr); }
    void visitLiteral(Literal curr) { rehash(digest, curr); }
    void visitType(Type curr) { rehash(digest, curr.getID()); }
    void visitIndex(Index curr) {
      static_assert(sizeof(Index) == sizeof(uint32_t),
                    "wasm64 will need changes here");
      rehash(digest, curr);
    }
    void visitAddress(Address curr) { rehash(digest, curr.addr); }
  };

  return Hasher(curr).digest;
}

} // namespace wasm
