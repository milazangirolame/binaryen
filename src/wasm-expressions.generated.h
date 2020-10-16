/*
 * Copyright 2020 WebAssembly Community Group participants
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

//=============================================================================
// This is an AUTOGENERATED file, even though it looks human-readable! Do not
// edit it by hand, instead edit what it is generated from. You can and should
// treat it like human-written code in all other ways, though, like reviewing
// it in a PR, etc.
//=============================================================================
class Nop : public SpecificExpression<Expression::NopId> {
public:
  Nop() {}
  Nop(MixedArena& allocator) : Nop() {}
  void finalize();
};
class Block : public SpecificExpression<Expression::BlockId> {
public:
  Block(MixedArena& allocator) : list(allocator) {}
  Name name;
  ExpressionList list;
  void finalize();
  void finalize(Type type_);
  void finalize(Type type_, bool hasBreak);
};
class If : public SpecificExpression<Expression::IfId> {
public:
  If() {}
  If(MixedArena& allocator) : If() {}
  Expression* condition;
  Expression* ifTrue;
  Expression* ifFalse = nullptr;
  void finalize(Type type_);
  void finalize();
};
class Loop : public SpecificExpression<Expression::LoopId> {
public:
  Loop() {}
  Loop(MixedArena& allocator) : Loop() {}
  Name name;
  Expression* body;
  void finalize(Type type_);
  void finalize();
};
class Break : public SpecificExpression<Expression::BreakId> {
public:
  Break() { type = Type::unreachable; }
  Break(MixedArena& allocator) : Break() {}
  Name name;
  Expression* value = nullptr;
  Expression* condition = nullptr;
  void finalize();
};
class Switch : public SpecificExpression<Expression::SwitchId> {
public:
  Switch(MixedArena& allocator) : targets(allocator) { type = Type::unreachable; }
  ArenaVector<Name> targets;
  Name default_;
  Expression* condition;
  Expression* value = nullptr;
  void finalize();
};
class Call : public SpecificExpression<Expression::CallId> {
public:
  Call(MixedArena& allocator) : operands(allocator) {}
  ExpressionList operands;
  Name target;
  bool isReturn;
  void finalize();
};
class CallIndirect : public SpecificExpression<Expression::CallIndirectId> {
public:
  CallIndirect(MixedArena& allocator) : operands(allocator) {}
  Signature sig;
  ExpressionList operands;
  Expression* target;
  bool isReturn;
  void finalize();
};
class LocalGet : public SpecificExpression<Expression::LocalGetId> {
public:
  LocalGet() {}
  LocalGet(MixedArena& allocator) : LocalGet() {}
  Index index;
  void finalize();
};
class LocalSet : public SpecificExpression<Expression::LocalSetId> {
public:
  LocalSet() {}
  LocalSet(MixedArena& allocator) : LocalSet() {}
  Index index;
  Expression* value;
  bool isTee() const;
  void makeTee(Type type);
  void makeSet();
  void finalize();
};
class GlobalGet : public SpecificExpression<Expression::GlobalGetId> {
public:
  GlobalGet() {}
  GlobalGet(MixedArena& allocator) : GlobalGet() {}
  Name name;
  void finalize();
};
class GlobalSet : public SpecificExpression<Expression::GlobalSetId> {
public:
  GlobalSet() {}
  GlobalSet(MixedArena& allocator) : GlobalSet() {}
  Name name;
  Expression* value;
  void finalize();
};
class Load : public SpecificExpression<Expression::LoadId> {
public:
  Load() {}
  Load(MixedArena& allocator) : Load() {}
  uint8_t bytes;
  bool signed_;
  Address offset;
  Address align;
  bool isAtomic;
  Expression* ptr;
  void finalize();
};
class Store : public SpecificExpression<Expression::StoreId> {
public:
  Store() {}
  Store(MixedArena& allocator) : Store() {}
  uint8_t bytes;
  Address offset;
  Address align;
  bool isAtomic;
  Expression* ptr;
  Expression* value;
  Type valueType;
  void finalize();
};
class AtomicRMW : public SpecificExpression<Expression::AtomicRMWId> {
public:
  AtomicRMW() {}
  AtomicRMW(MixedArena& allocator) : AtomicRMW() {}
  AtomicRMWOp op;
  uint8_t bytes;
  Address offset;
  Expression* ptr;
  Expression* value;
  void finalize();
};
class AtomicCmpxchg : public SpecificExpression<Expression::AtomicCmpxchgId> {
public:
  AtomicCmpxchg() {}
  AtomicCmpxchg(MixedArena& allocator) : AtomicCmpxchg() {}
  uint8_t bytes;
  Address offset;
  Expression* ptr;
  Expression* expected;
  Expression* replacement;
  void finalize();
};
class AtomicWait : public SpecificExpression<Expression::AtomicWaitId> {
public:
  AtomicWait() {}
  AtomicWait(MixedArena& allocator) : AtomicWait() {}
  Address offset;
  Expression* ptr;
  Expression* expected;
  Expression* timeout;
  Type expectedType;
  void finalize();
};
class AtomicNotify : public SpecificExpression<Expression::AtomicNotifyId> {
public:
  AtomicNotify() {}
  AtomicNotify(MixedArena& allocator) : AtomicNotify() {}
  Address offset;
  Expression* ptr;
  Expression* notifyCount;
  void finalize();
};
class AtomicFence : public SpecificExpression<Expression::AtomicFenceId> {
public:
  AtomicFence() {}
  AtomicFence(MixedArena& allocator) : AtomicFence() {}
  uint8_t order;
  void finalize();
};
class SIMDExtract : public SpecificExpression<Expression::SIMDExtractId> {
public:
  SIMDExtract() {}
  SIMDExtract(MixedArena& allocator) : SIMDExtract() {}
  Expression* vec;
  uint8_t index;
  void finalize();
};
class SIMDReplace : public SpecificExpression<Expression::SIMDReplaceId> {
public:
  SIMDReplace() {}
  SIMDReplace(MixedArena& allocator) : SIMDReplace() {}
  Expression* vec;
  uint8_t index;
  Expression* value;
  void finalize();
};
class SIMDShuffle : public SpecificExpression<Expression::SIMDShuffleId> {
public:
  SIMDShuffle() {}
  SIMDShuffle(MixedArena& allocator) : SIMDShuffle() {}
  Expression* left;
  Expression* right;
  void finalize();
};
class SIMDTernary : public SpecificExpression<Expression::SIMDTernaryId> {
public:
  SIMDTernary() {}
  SIMDTernary(MixedArena& allocator) : SIMDTernary() {}
  Expression* a;
  Expression* b;
  Expression* c;
  void finalize();
};
class SIMDShift : public SpecificExpression<Expression::SIMDShiftId> {
public:
  SIMDShift() {}
  SIMDShift(MixedArena& allocator) : SIMDShift() {}
  Expression* vec;
  Expression* shift;
  void finalize();
};
class SIMDLoad : public SpecificExpression<Expression::SIMDLoadId> {
public:
  SIMDLoad() {}
  SIMDLoad(MixedArena& allocator) : SIMDLoad() {}
  Address offset;
  Address align;
  Expression* ptr;
  Index getMemBytes();
  void finalize();
};
class MemoryInit : public SpecificExpression<Expression::MemoryInitId> {
public:
  MemoryInit() {}
  MemoryInit(MixedArena& allocator) : MemoryInit() {}
  Index segment;
  Expression* dest;
  Expression* offset;
  Expression* size;
  void finalize();
};
class DataDrop : public SpecificExpression<Expression::DataDropId> {
public:
  DataDrop() {}
  DataDrop(MixedArena& allocator) : DataDrop() {}
  Index segment;
  void finalize();
};
class MemoryCopy : public SpecificExpression<Expression::MemoryCopyId> {
public:
  MemoryCopy() {}
  MemoryCopy(MixedArena& allocator) : MemoryCopy() {}
  Expression* dest;
  Expression* source;
  Expression* size;
  void finalize();
};
class MemoryFill : public SpecificExpression<Expression::MemoryFillId> {
public:
  MemoryFill() {}
  MemoryFill(MixedArena& allocator) : MemoryFill() {}
  Expression* dest;
  Expression* value;
  Expression* size;
  void finalize();
};
class Const : public SpecificExpression<Expression::ConstId> {
public:
  Const() {}
  Const(MixedArena& allocator) : Const() {}
  Const* set(Literal value_);
  void finalize();
};
class Unary : public SpecificExpression<Expression::UnaryId> {
public:
  Unary() {}
  Unary(MixedArena& allocator) : Unary() {}
  Expression* value;
  bool isRelational();
  void finalize();
};
class Binary : public SpecificExpression<Expression::BinaryId> {
public:
  Binary() {}
  Binary(MixedArena& allocator) : Binary() {}
  Expression* left;
  Expression* right;
  bool isRelational();
  void finalize();
};
class Select : public SpecificExpression<Expression::SelectId> {
public:
  Select() {}
  Select(MixedArena& allocator) : Select() {}
  Expression* ifTrue;
  Expression* ifFalse;
  Expression* condition;
  void finalize();
  void finalize(Type type_);
};
class Drop : public SpecificExpression<Expression::DropId> {
public:
  Drop() {}
  Drop(MixedArena& allocator) : Drop() {}
  Expression* value;
  void finalize();
};
class Return : public SpecificExpression<Expression::ReturnId> {
public:
  Return() {}
  Return(MixedArena& allocator) : Return() {}
  Expression* value = nullptr;
  void finalize();
};
class MemorySize : public SpecificExpression<Expression::MemorySizeId> {
public:
  MemorySize() { type = Type::i32; }
  MemorySize(MixedArena& allocator) : MemorySize() {}
  Type ptrType = Type::i32;
  void make64();
  void finalize();
};
class MemoryGrow : public SpecificExpression<Expression::MemoryGrowId> {
public:
  MemoryGrow() {}
  MemoryGrow(MixedArena& allocator) : MemoryGrow() {}
  Expression* delta = nullptr;
  Type ptrType = Type::i32;
  void make64();
  void finalize();
};
class Unreachable : public SpecificExpression<Expression::UnreachableId> {
public:
  Unreachable() { type = Type::unreachable; }
  Unreachable(MixedArena& allocator) : Unreachable() {}
  void finalize();
};
class Pop : public SpecificExpression<Expression::PopId> {
public:
  Pop() {}
  Pop(MixedArena& allocator) : Pop() {}
  void finalize();
};
class RefNull : public SpecificExpression<Expression::RefNullId> {
public:
  RefNull() {}
  RefNull(MixedArena& allocator) : RefNull() {}
  void finalize();
  void finalize(HeapType heapType);
  void finalize(Type type);
};
class RefIsNull : public SpecificExpression<Expression::RefIsNullId> {
public:
  RefIsNull() {}
  RefIsNull(MixedArena& allocator) : RefIsNull() {}
  Expression* value;
  void finalize();
};
class RefFunc : public SpecificExpression<Expression::RefFuncId> {
public:
  RefFunc() {}
  RefFunc(MixedArena& allocator) : RefFunc() {}
  Name func;
  void finalize();
};
class RefEq : public SpecificExpression<Expression::RefEqId> {
public:
  RefEq() {}
  RefEq(MixedArena& allocator) : RefEq() {}
  Expression* left;
  Expression* right;
  void finalize();
};
class Try : public SpecificExpression<Expression::TryId> {
public:
  Try() {}
  Try(MixedArena& allocator) : Try() {}
  Expression* body;
  Expression* catchBody;
  void finalize();
  void finalize(Type type_);
};
class Throw : public SpecificExpression<Expression::ThrowId> {
public:
  Throw(MixedArena& allocator) : operands(allocator) {}
  Name event;
  ExpressionList operands;
  void finalize();
};
class Rethrow : public SpecificExpression<Expression::RethrowId> {
public:
  Rethrow() {}
  Rethrow(MixedArena& allocator) : Rethrow() {}
  Expression* exnref;
  void finalize();
};
class BrOnExn : public SpecificExpression<Expression::BrOnExnId> {
public:
  BrOnExn() { type = Type::unreachable; }
  BrOnExn(MixedArena& allocator) : BrOnExn() {}
  Name name;
  Name event;
  Expression* exnref;
  Type send;
  void finalize();
};
class TupleMake : public SpecificExpression<Expression::TupleMakeId> {
public:
  TupleMake(MixedArena& allocator) : operands(allocator) {}
  ExpressionList operands;
  void finalize();
};
class TupleExtract : public SpecificExpression<Expression::TupleExtractId> {
public:
  TupleExtract() {}
  TupleExtract(MixedArena& allocator) : TupleExtract() {}
  Expression* tuple;
  Index index;
  void finalize();
};
class I31New : public SpecificExpression<Expression::I31NewId> {
public:
  I31New() {}
  I31New(MixedArena& allocator) : I31New() {}
  Expression* value;
  void finalize();
};
class I31Get : public SpecificExpression<Expression::I31GetId> {
public:
  I31Get() {}
  I31Get(MixedArena& allocator) : I31Get() {}
  Expression* i31;
  bool signed_;
  void finalize();
};
class RefTest : public SpecificExpression<Expression::RefTestId> {
public:
  RefTest() {}
  RefTest(MixedArena& allocator) : RefTest() {}
  void finalize();
};
class RefCast : public SpecificExpression<Expression::RefCastId> {
public:
  RefCast() {}
  RefCast(MixedArena& allocator) : RefCast() {}
  void finalize();
};
class BrOnCast : public SpecificExpression<Expression::BrOnCastId> {
public:
  BrOnCast() {}
  BrOnCast(MixedArena& allocator) : BrOnCast() {}
  void finalize();
};
class RttCanon : public SpecificExpression<Expression::RttCanonId> {
public:
  RttCanon() {}
  RttCanon(MixedArena& allocator) : RttCanon() {}
  void finalize();
};
class RttSub : public SpecificExpression<Expression::RttSubId> {
public:
  RttSub() {}
  RttSub(MixedArena& allocator) : RttSub() {}
  void finalize();
};
class StructNew : public SpecificExpression<Expression::StructNewId> {
public:
  StructNew() {}
  StructNew(MixedArena& allocator) : StructNew() {}
  void finalize();
};
class StructGet : public SpecificExpression<Expression::StructGetId> {
public:
  StructGet() {}
  StructGet(MixedArena& allocator) : StructGet() {}
  void finalize();
};
class StructSet : public SpecificExpression<Expression::StructSetId> {
public:
  StructSet() {}
  StructSet(MixedArena& allocator) : StructSet() {}
  void finalize();
};
class ArrayNew : public SpecificExpression<Expression::ArrayNewId> {
public:
  ArrayNew() {}
  ArrayNew(MixedArena& allocator) : ArrayNew() {}
  void finalize();
};
class ArrayGet : public SpecificExpression<Expression::ArrayGetId> {
public:
  ArrayGet() {}
  ArrayGet(MixedArena& allocator) : ArrayGet() {}
  void finalize();
};
class ArraySet : public SpecificExpression<Expression::ArraySetId> {
public:
  ArraySet() {}
  ArraySet(MixedArena& allocator) : ArraySet() {}
  void finalize();
};
class ArrayLen : public SpecificExpression<Expression::ArrayLenId> {
public:
  ArrayLen() {}
  ArrayLen(MixedArena& allocator) : ArrayLen() {}
  void finalize();
};
