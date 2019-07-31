#ifndef DEBUG_HH
#define DEBUG_HH

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "chunk.hh"

class Debuger
{
public:
  void Disassemble(const Chunk &chunk, std::string name) const
  {
    std::cout << "=========== " << name << " ===========\n\n";
    std::cout << "OFFSET\tLINE\tOPERATION\tOPRAND\n\n";
    auto size_code = chunk.size();
    for (size_t offset = 0; offset < size_code;)
    {
      offset = DisassembleInstruction(chunk, offset);
    }
  }
private:
  size_t DisassembleInstruction(const Chunk &chunk, size_t offset) const
  {
    std::cout << std::setfill('0') << std::setw(4) << offset << "\t";
    auto line_num = chunk.GetLineNum(offset);
    // std::cout << "\n";
    // std::cout << "line num = " << line_num.line_number() << " " << line_num.len_continuous()
    //   << " " << line_num.len_accumulated() << "\n";
    // std::cout << "line start offset = " << line_num.len_accumulated() - line_num.len_continuous() << "\n";
    // std::cout << "offset = " << offset << "\n";
    if(offset == line_num.len_accumulated() - line_num.len_continuous())
    {
      std::cout << std::setfill('0') << std::setw(4) << line_num.line_number() << "\t";
    }
    else
    {
      std::cout << "   |\t";
    }
    auto instruction = chunk[offset];
    // TODO: change switch to hash<OpCode, function>
    switch(instruction){
      case OpCode::OP_RETURN:
      {
        return SimpleInstruction("OP_RETURN", offset);
      }
      case OpCode::OP_UNKNOWN:
      {
        return SimpleInstruction("OP_UNKNOWN", offset);
      }
      case OpCode::OP_CONSTANT:
      {
        return ConstantInstruction(chunk, "OP_CONSTANT", offset);
      }
      case OpCode::OP_RESERVED:
      {
        return SimpleInstruction("OP_RESERVED", offset);
      }
      default:
      {
        std::cout << "undefined operation\n";
        return ++offset;
      }
    }
  }
  size_t SimpleInstruction(std::string &&op_name, size_t offset) const
  {
    std::cout << op_name << "\n";
    return ++offset;
  }
  size_t ConstantInstruction(const Chunk &chunk, std::string &&op_name, size_t offset) const
  {
    // std::cout << "chunk size = " << chunk.size() << "\n";
    size_t address = 0;
    offset++;
    for (size_t idx = 0; idx < Chunk::LEN_SIZE_T; idx++)
    {
      // std::cout << idx << " " << idx + offset << "\t" << static_cast<size_t>(chunk[idx + offset]) << "\n";
      address += static_cast<size_t>(chunk[idx + offset]) * pow(256, idx);
    }
    // std::cout << "address = " << address << "\n";
    std::cout << op_name << "\t" << chunk.constant(address) << " @" << offset << "\n";
    return offset + 8;
  }
};

#endif // DEBUG_HH
