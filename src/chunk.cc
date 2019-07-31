#include <stdio.h>
#include "chunk.hh"

void Chunk::Write(OpCode byte)
{
  code_.push_back(std::move(byte));
}

void Chunk::Write(ConstantAddress address)
{
  for (size_t idx = 0; idx < LEN_SIZE_T; idx++)
  {
    code_.push_back(static_cast<OpCode>(address[idx]));
  }
}

ConstantAddress Chunk::AddConstant(Value value)
{
  constants_.push_back(value);
  return ConstantAddress(constants_.size() - 1); // TODO: maybe need thread protection
}

OpCode Chunk::operator[](size_t i) const
{
  if(i < code_.size())
  {
    return code_[i];
  }
  return OpCode::OP_UNKNOWN;
}