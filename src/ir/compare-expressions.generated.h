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
  // edit it by hand, instead edit the generator, gen-exprs.py
  //
  // You can and should treat it like human-written code in all other ways,
  // though, like reviewing it in a PR, etc.
  //=============================================================================

case Expression::NopId: {
  break;
}
case Expression::BlockId: {
  auto* castLeft = left->cast<Block>();
  auto* castRight = right->cast<Block>();
  if (castLeft->name.is() != castRight->name.is()) {
    return false;
  }
  rightNames[castLeft->name] = castRight->name;
  if (castLeft->list.size() != castRight->list.size()) {
    return false;
  }
  for (auto* child : castLeft->list) {
    leftStack.push_back(child);
  }
  for (auto* child : castRight->list) {
    rightStack.push_back(child);
  }
  break;
}
case Expression::IfId: {
  auto* castLeft = left->cast<If>();
  auto* castRight = right->cast<If>();
  leftStack.push_back(castLeft->condition);
  rightStack.push_back(castRight->condition);
  leftStack.push_back(castLeft->ifTrue);
  rightStack.push_back(castRight->ifTrue);
  leftStack.push_back(castLeft->ifFalse);
  rightStack.push_back(castRight->ifFalse);
  break;
}
case Expression::LoopId: {
  auto* castLeft = left->cast<Loop>();
  auto* castRight = right->cast<Loop>();
  if (castLeft->name.is() != castRight->name.is()) {
    return false;
  }
  rightNames[castLeft->name] = castRight->name;
  leftStack.push_back(castLeft->body);
  rightStack.push_back(castRight->body);
  break;
}
case Expression::BreakId: {
  auto* castLeft = left->cast<Break>();
  auto* castRight = right->cast<Break>();
  if (!compareNames(castLeft->name, castRight->name)) {
    return false;
  }
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  leftStack.push_back(castLeft->condition);
  rightStack.push_back(castRight->condition);
  break;
}
case Expression::SwitchId: {
  auto* castLeft = left->cast<Switch>();
  auto* castRight = right->cast<Switch>();
  if (castLeft->targets.size() != castRight->targets.size()) {
    return false;
  }
  for (Index i = 0; i < castLeft->targets.size(); i++) {
    if (!compareNames(castLeft->targets[i], castRight->targets[i])) {
      return false;
    }
  }
  if (!compareNames(castLeft->default_, castRight->default_)) {
    return false;
  }
  leftStack.push_back(castLeft->condition);
  rightStack.push_back(castRight->condition);
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::CallId: {
  auto* castLeft = left->cast<Call>();
  auto* castRight = right->cast<Call>();
  if (castLeft->operands.size() != castRight->operands.size()) {
    return false;
  }
  for (auto* child : castLeft->operands) {
    leftStack.push_back(child);
  }
  for (auto* child : castRight->operands) {
    rightStack.push_back(child);
  }
  if (castLeft->target != castRight->target) {
    return false;
  }
  if (castLeft->isReturn != castRight->isReturn) {
    return false;
  }
  break;
}
case Expression::CallIndirectId: {
  auto* castLeft = left->cast<CallIndirect>();
  auto* castRight = right->cast<CallIndirect>();
  if (castLeft->sig != castRight->sig) {
    return false;
  }
  if (castLeft->operands.size() != castRight->operands.size()) {
    return false;
  }
  for (auto* child : castLeft->operands) {
    leftStack.push_back(child);
  }
  for (auto* child : castRight->operands) {
    rightStack.push_back(child);
  }
  leftStack.push_back(castLeft->target);
  rightStack.push_back(castRight->target);
  if (castLeft->isReturn != castRight->isReturn) {
    return false;
  }
  break;
}
case Expression::LocalGetId: {
  auto* castLeft = left->cast<LocalGet>();
  auto* castRight = right->cast<LocalGet>();
  if (castLeft->index != castRight->index) {
    return false;
  }
  break;
}
case Expression::LocalSetId: {
  auto* castLeft = left->cast<LocalSet>();
  auto* castRight = right->cast<LocalSet>();
  if (castLeft->index != castRight->index) {
    return false;
  }
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::GlobalGetId: {
  auto* castLeft = left->cast<GlobalGet>();
  auto* castRight = right->cast<GlobalGet>();
  if (castLeft->name != castRight->name) {
    return false;
  }
  break;
}
case Expression::GlobalSetId: {
  auto* castLeft = left->cast<GlobalSet>();
  auto* castRight = right->cast<GlobalSet>();
  if (castLeft->name != castRight->name) {
    return false;
  }
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::LoadId: {
  auto* castLeft = left->cast<Load>();
  auto* castRight = right->cast<Load>();
  if (castLeft->bytes != castRight->bytes) {
    return false;
  }
  if (LoadUtils::isSignRelevant(castLeft)) {
    if (castLeft->signed_ != castRight->signed_) {
      return false;
    }
  }
  if (castLeft->offset != castRight->offset) {
    return false;
  }
  if (castLeft->align != castRight->align) {
    return false;
  }
  if (castLeft->isAtomic != castRight->isAtomic) {
    return false;
  }
  leftStack.push_back(castLeft->ptr);
  rightStack.push_back(castRight->ptr);
  break;
}
case Expression::StoreId: {
  auto* castLeft = left->cast<Store>();
  auto* castRight = right->cast<Store>();
  if (castLeft->bytes != castRight->bytes) {
    return false;
  }
  if (castLeft->offset != castRight->offset) {
    return false;
  }
  if (castLeft->align != castRight->align) {
    return false;
  }
  if (castLeft->isAtomic != castRight->isAtomic) {
    return false;
  }
  leftStack.push_back(castLeft->ptr);
  rightStack.push_back(castRight->ptr);
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  if (castLeft->valueType != castRight->valueType) {
    return false;
  }
  break;
}
case Expression::AtomicRMWId: {
  auto* castLeft = left->cast<AtomicRMW>();
  auto* castRight = right->cast<AtomicRMW>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  if (castLeft->bytes != castRight->bytes) {
    return false;
  }
  if (castLeft->offset != castRight->offset) {
    return false;
  }
  leftStack.push_back(castLeft->ptr);
  rightStack.push_back(castRight->ptr);
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::AtomicCmpxchgId: {
  auto* castLeft = left->cast<AtomicCmpxchg>();
  auto* castRight = right->cast<AtomicCmpxchg>();
  if (castLeft->bytes != castRight->bytes) {
    return false;
  }
  if (castLeft->offset != castRight->offset) {
    return false;
  }
  leftStack.push_back(castLeft->ptr);
  rightStack.push_back(castRight->ptr);
  leftStack.push_back(castLeft->expected);
  rightStack.push_back(castRight->expected);
  leftStack.push_back(castLeft->replacement);
  rightStack.push_back(castRight->replacement);
  break;
}
case Expression::AtomicWaitId: {
  auto* castLeft = left->cast<AtomicWait>();
  auto* castRight = right->cast<AtomicWait>();
  if (castLeft->offset != castRight->offset) {
    return false;
  }
  leftStack.push_back(castLeft->ptr);
  rightStack.push_back(castRight->ptr);
  leftStack.push_back(castLeft->expected);
  rightStack.push_back(castRight->expected);
  leftStack.push_back(castLeft->timeout);
  rightStack.push_back(castRight->timeout);
  if (castLeft->expectedType != castRight->expectedType) {
    return false;
  }
  break;
}
case Expression::AtomicNotifyId: {
  auto* castLeft = left->cast<AtomicNotify>();
  auto* castRight = right->cast<AtomicNotify>();
  if (castLeft->offset != castRight->offset) {
    return false;
  }
  leftStack.push_back(castLeft->ptr);
  rightStack.push_back(castRight->ptr);
  leftStack.push_back(castLeft->notifyCount);
  rightStack.push_back(castRight->notifyCount);
  break;
}
case Expression::AtomicFenceId: {
  auto* castLeft = left->cast<AtomicFence>();
  auto* castRight = right->cast<AtomicFence>();
  if (castLeft->order != castRight->order) {
    return false;
  }
  break;
}
case Expression::SIMDExtractId: {
  auto* castLeft = left->cast<SIMDExtract>();
  auto* castRight = right->cast<SIMDExtract>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  leftStack.push_back(castLeft->vec);
  rightStack.push_back(castRight->vec);
  if (castLeft->index != castRight->index) {
    return false;
  }
  break;
}
case Expression::SIMDReplaceId: {
  auto* castLeft = left->cast<SIMDReplace>();
  auto* castRight = right->cast<SIMDReplace>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  leftStack.push_back(castLeft->vec);
  rightStack.push_back(castRight->vec);
  if (castLeft->index != castRight->index) {
    return false;
  }
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::SIMDShuffleId: {
  auto* castLeft = left->cast<SIMDShuffle>();
  auto* castRight = right->cast<SIMDShuffle>();
  leftStack.push_back(castLeft->left);
  rightStack.push_back(castRight->left);
  leftStack.push_back(castLeft->right);
  rightStack.push_back(castRight->right);
  if (castLeft->mask != castRight->mask) {
    return false;
  }
  break;
}
case Expression::SIMDTernaryId: {
  auto* castLeft = left->cast<SIMDTernary>();
  auto* castRight = right->cast<SIMDTernary>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  leftStack.push_back(castLeft->a);
  rightStack.push_back(castRight->a);
  leftStack.push_back(castLeft->b);
  rightStack.push_back(castRight->b);
  leftStack.push_back(castLeft->c);
  rightStack.push_back(castRight->c);
  break;
}
case Expression::SIMDShiftId: {
  auto* castLeft = left->cast<SIMDShift>();
  auto* castRight = right->cast<SIMDShift>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  leftStack.push_back(castLeft->vec);
  rightStack.push_back(castRight->vec);
  leftStack.push_back(castLeft->shift);
  rightStack.push_back(castRight->shift);
  break;
}
case Expression::SIMDLoadId: {
  auto* castLeft = left->cast<SIMDLoad>();
  auto* castRight = right->cast<SIMDLoad>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  if (castLeft->offset != castRight->offset) {
    return false;
  }
  if (castLeft->align != castRight->align) {
    return false;
  }
  leftStack.push_back(castLeft->ptr);
  rightStack.push_back(castRight->ptr);
  break;
}
case Expression::MemoryInitId: {
  auto* castLeft = left->cast<MemoryInit>();
  auto* castRight = right->cast<MemoryInit>();
  if (castLeft->segment != castRight->segment) {
    return false;
  }
  leftStack.push_back(castLeft->dest);
  rightStack.push_back(castRight->dest);
  leftStack.push_back(castLeft->offset);
  rightStack.push_back(castRight->offset);
  leftStack.push_back(castLeft->size);
  rightStack.push_back(castRight->size);
  break;
}
case Expression::DataDropId: {
  auto* castLeft = left->cast<DataDrop>();
  auto* castRight = right->cast<DataDrop>();
  if (castLeft->segment != castRight->segment) {
    return false;
  }
  break;
}
case Expression::MemoryCopyId: {
  auto* castLeft = left->cast<MemoryCopy>();
  auto* castRight = right->cast<MemoryCopy>();
  leftStack.push_back(castLeft->dest);
  rightStack.push_back(castRight->dest);
  leftStack.push_back(castLeft->source);
  rightStack.push_back(castRight->source);
  leftStack.push_back(castLeft->size);
  rightStack.push_back(castRight->size);
  break;
}
case Expression::MemoryFillId: {
  auto* castLeft = left->cast<MemoryFill>();
  auto* castRight = right->cast<MemoryFill>();
  leftStack.push_back(castLeft->dest);
  rightStack.push_back(castRight->dest);
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  leftStack.push_back(castLeft->size);
  rightStack.push_back(castRight->size);
  break;
}
case Expression::ConstId: {
  auto* castLeft = left->cast<Const>();
  auto* castRight = right->cast<Const>();
  if (castLeft->value != castRight->value) {
    return false;
  }
  break;
}
case Expression::UnaryId: {
  auto* castLeft = left->cast<Unary>();
  auto* castRight = right->cast<Unary>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::BinaryId: {
  auto* castLeft = left->cast<Binary>();
  auto* castRight = right->cast<Binary>();
  if (castLeft->op != castRight->op) {
    return false;
  }
  leftStack.push_back(castLeft->left);
  rightStack.push_back(castRight->left);
  leftStack.push_back(castLeft->right);
  rightStack.push_back(castRight->right);
  break;
}
case Expression::SelectId: {
  auto* castLeft = left->cast<Select>();
  auto* castRight = right->cast<Select>();
  leftStack.push_back(castLeft->ifTrue);
  rightStack.push_back(castRight->ifTrue);
  leftStack.push_back(castLeft->ifFalse);
  rightStack.push_back(castRight->ifFalse);
  leftStack.push_back(castLeft->condition);
  rightStack.push_back(castRight->condition);
  break;
}
case Expression::DropId: {
  auto* castLeft = left->cast<Drop>();
  auto* castRight = right->cast<Drop>();
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::ReturnId: {
  auto* castLeft = left->cast<Return>();
  auto* castRight = right->cast<Return>();
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::MemorySizeId: {
  auto* castLeft = left->cast<MemorySize>();
  auto* castRight = right->cast<MemorySize>();
  if (castLeft->ptrType != castRight->ptrType) {
    return false;
  }
  break;
}
case Expression::MemoryGrowId: {
  auto* castLeft = left->cast<MemoryGrow>();
  auto* castRight = right->cast<MemoryGrow>();
  leftStack.push_back(castLeft->delta);
  rightStack.push_back(castRight->delta);
  if (castLeft->ptrType != castRight->ptrType) {
    return false;
  }
  break;
}
case Expression::UnreachableId: {
  break;
}
case Expression::PopId: {
  break;
}
case Expression::RefNullId: {
  break;
}
case Expression::RefIsNullId: {
  auto* castLeft = left->cast<RefIsNull>();
  auto* castRight = right->cast<RefIsNull>();
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::RefFuncId: {
  auto* castLeft = left->cast<RefFunc>();
  auto* castRight = right->cast<RefFunc>();
  if (castLeft->func != castRight->func) {
    return false;
  }
  break;
}
case Expression::RefEqId: {
  auto* castLeft = left->cast<RefEq>();
  auto* castRight = right->cast<RefEq>();
  leftStack.push_back(castLeft->left);
  rightStack.push_back(castRight->left);
  leftStack.push_back(castLeft->right);
  rightStack.push_back(castRight->right);
  break;
}
case Expression::TryId: {
  auto* castLeft = left->cast<Try>();
  auto* castRight = right->cast<Try>();
  leftStack.push_back(castLeft->body);
  rightStack.push_back(castRight->body);
  leftStack.push_back(castLeft->catchBody);
  rightStack.push_back(castRight->catchBody);
  break;
}
case Expression::ThrowId: {
  auto* castLeft = left->cast<Throw>();
  auto* castRight = right->cast<Throw>();
  if (castLeft->event != castRight->event) {
    return false;
  }
  if (castLeft->operands.size() != castRight->operands.size()) {
    return false;
  }
  for (auto* child : castLeft->operands) {
    leftStack.push_back(child);
  }
  for (auto* child : castRight->operands) {
    rightStack.push_back(child);
  }
  break;
}
case Expression::RethrowId: {
  auto* castLeft = left->cast<Rethrow>();
  auto* castRight = right->cast<Rethrow>();
  leftStack.push_back(castLeft->exnref);
  rightStack.push_back(castRight->exnref);
  break;
}
case Expression::BrOnExnId: {
  auto* castLeft = left->cast<BrOnExn>();
  auto* castRight = right->cast<BrOnExn>();
  if (!compareNames(castLeft->name, castRight->name)) {
    return false;
  }
  if (castLeft->event != castRight->event) {
    return false;
  }
  leftStack.push_back(castLeft->exnref);
  rightStack.push_back(castRight->exnref);
  if (castLeft->sent != castRight->sent) {
    return false;
  }
  break;
}
case Expression::TupleMakeId: {
  auto* castLeft = left->cast<TupleMake>();
  auto* castRight = right->cast<TupleMake>();
  if (castLeft->operands.size() != castRight->operands.size()) {
    return false;
  }
  for (auto* child : castLeft->operands) {
    leftStack.push_back(child);
  }
  for (auto* child : castRight->operands) {
    rightStack.push_back(child);
  }
  break;
}
case Expression::TupleExtractId: {
  auto* castLeft = left->cast<TupleExtract>();
  auto* castRight = right->cast<TupleExtract>();
  leftStack.push_back(castLeft->tuple);
  rightStack.push_back(castRight->tuple);
  if (castLeft->index != castRight->index) {
    return false;
  }
  break;
}
case Expression::I31NewId: {
  auto* castLeft = left->cast<I31New>();
  auto* castRight = right->cast<I31New>();
  leftStack.push_back(castLeft->value);
  rightStack.push_back(castRight->value);
  break;
}
case Expression::I31GetId: {
  auto* castLeft = left->cast<I31Get>();
  auto* castRight = right->cast<I31Get>();
  leftStack.push_back(castLeft->i31);
  rightStack.push_back(castRight->i31);
  if (castLeft->signed_ != castRight->signed_) {
    return false;
  }
  break;
}
case Expression::RefTestId: {
  break;
}
case Expression::RefCastId: {
  break;
}
case Expression::BrOnCastId: {
  break;
}
case Expression::RttCanonId: {
  break;
}
case Expression::RttSubId: {
  break;
}
case Expression::StructNewId: {
  break;
}
case Expression::StructGetId: {
  break;
}
case Expression::StructSetId: {
  break;
}
case Expression::ArrayNewId: {
  break;
}
case Expression::ArrayGetId: {
  break;
}
case Expression::ArraySetId: {
  break;
}
case Expression::ArrayLenId: {
  break;
}
