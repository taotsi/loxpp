#ifndef DEBUG_HH
#define DEBUG_HH

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "chunk.hh"
#include "msg.hh"

namespace loxpp{

using namespace taotsi;

class Debuger
{
public:
  void Disassemble(const Chunk &chunk, std::string name) const
  {
    std::cout << "=========== " << name << " ===========\n";
    std::cout << "OFFSET\tLINE\tOPCODE\t\tOPRAND\n--------------------------------------\n";
    auto size_code = chunk.size();
    for (size_t offset = 0; offset < size_code;)
    {
      // tval(offset);
      offset = DisassembleInstruction(chunk, offset);
    }
  }

private:
  friend class VM;
  static size_t DisassembleInstruction(const Chunk &chunk, size_t offset)
  {
    std::cout << std::setfill('0') << std::setw(4) << offset << "\t";
    auto line_num = chunk.GetLineNum(offset);
    // tval(line_num.line_number());
    if(offset == line_num.len_accumulated() - line_num.len_continuous())
    {
      std::cout << std::setfill('0') << std::setw(4) << line_num.line_number() << "\t";
    }
    else
    {
      std::cout << "   |\t";
    }
    // tval(chunk.size());
    // tval(offset);
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
      case OpCode::OP_NEGATE:
      {
        return SimpleInstruction("OP_NEGATE", offset);
      }
      case OpCode::OP_ADD:
      {
        return SimpleInstruction("OP_ADD", offset);
      }
      case OpCode::OP_SUBTRACT:
      {
        return SimpleInstruction("OP_SUBTRACT", offset);
      }
      case OpCode::OP_MULTIPLY:
      {
        return SimpleInstruction("OP_NEGAOP_MULTIPLYTE", offset);
      }
      case OpCode::OP_DIVIDE:
      {
        return SimpleInstruction("OP_DIVIDE", offset);      }
      default:
      {
        std::cout << "undefined operation\n";
        return ++offset;
      }
    }
  }
  static size_t SimpleInstruction(std::string &&op_name, size_t offset)
  {
    std::cout << op_name << "\n";
    return ++offset;
  }
  static size_t ConstantInstruction(const Chunk &chunk, std::string &&op_name, size_t offset)
  {
    size_t address = 0;
    offset++;
    for (size_t idx = 0; idx < Chunk::LEN_SIZE_T; idx++)
    {
      // tval(idx+offset);
      // tval(static_cast<size_t>(chunk[idx + offset]));
      address |= static_cast<size_t>(chunk[idx + offset]) << 8*(Chunk::LEN_SIZE_T - idx - 1);
    }
    // tval(address);
    // tval(offset + Chunk::LEN_SIZE_T);
    std::cout << op_name << "\t" << chunk.constant(address) << "\t@" << offset << "\n";
    return offset + Chunk::LEN_SIZE_T;
  }
};

}

#endif // DEBUG_HH
