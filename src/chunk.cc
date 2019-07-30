#include <stdio.h>
#include "chunk.hh"

void Chunk::Write(OpCode byte)
{
  code_.push_back(std::move(byte));
}
size_t Chunk::AddConstant(Value value)
{
  constants_.push_back(value);
  return constants_.size() - 1;
}

OpCode Chunk::operator[](size_t i) const
{
  if(i < code_.size()){
    return code_[i];
  }
  return OpCode::OP_UNKNOWN;
}