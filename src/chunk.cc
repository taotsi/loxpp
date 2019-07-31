#include <iostream>
#include "chunk.hh"

Chunk::Chunk()
{
  code_.push_back(OpCode::OP_RESERVED);
  line_numbers_.push_back(LineNumber{0, 1, 1});
}

void Chunk::Write(OpCode byte, size_t line_num)
{
  code_.push_back(std::move(byte));
  if(line_num == line_numbers_.back().line_number())
  {
    line_numbers_.back().len_advance(1);
  }
  else
  {
    line_numbers_.push_back(
      LineNumber{line_num, 1, line_numbers_.back().len_accumulated()+1});
  }
}

void Chunk::Write(ConstantAddress address, size_t line_num)
{
  for (size_t idx = 0; idx < LEN_SIZE_T; idx++)
  {
    code_.push_back(static_cast<OpCode>(address[idx])); // TODO: maybe need thread protection
  }
  if(line_num == line_numbers_.back().line_number())
  {
    line_numbers_.back().len_advance(LEN_SIZE_T);
  }
  else
  {
    line_numbers_.push_back(
      LineNumber{line_num, LEN_SIZE_T, line_numbers_.back().len_accumulated()+LEN_SIZE_T});
  }
}

ConstantAddress Chunk::AddConstant(Value value)
{
  constants_.push_back(value);
  return ConstantAddress{constants_.size() - 1}; // TODO: maybe need thread protection
}

OpCode Chunk::operator[](size_t i) const
{
  if(i < code_.size())
  {
    return code_[i];
  }
  std::cout << "chunk[] out of range\n";
  return OpCode::OP_UNKNOWN;
}

LineNumber Chunk::GetLineNum(size_t offset) const
{
  auto size_line_nums = line_numbers_.size();
  // TODO: use binary search instead
  for (size_t i = 0; i < size_line_nums; i++)
  {
    if(offset < line_numbers_[i].len_accumulated())
    {
      return line_numbers_[i];
    }
  }
  std::cout << "no such a offset matched a line number!\n";
  return LineNumber{0, 0, 0};
}