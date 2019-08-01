#include <memory>
#include <iostream>
#include <cmath>
#include "utility.hh"
#include "vm.hh"
#include "debuger.hh"

#define DEBUG_TRACE_EXECUTION

namespace loxpp
{
VM::VM()
{

}
// VM::VM(std::shared_ptr<Chunk> chunk)
//   : chunk_ptr_{chunk}
// {

// }

InterpretResult VM::Interpret(std::shared_ptr<Chunk> chunk)
{
  chunk_ptr_ = chunk;
  ip_ = 0;
  return Run();
}

InterpretResult VM::Run()
{
  bool is_end = false;
  auto n_instruc = chunk_ptr_->size();
  while(ip_ < n_instruc)
  {
#ifdef DEBUG_TRACE_EXECUTION
    Debuger::DisassembleInstruction(*chunk_ptr_, ip_);
#endif
    OpCode instruct;
    switch(instruct = IpRead())
    {
      case OpCode::OP_RETURN:
      {
        return InterpretResult::INTERPRET_OK;
      }
      case OpCode::OP_CONSTANT:
      {
        Value constant = ReadConstant();
        // lmark();
        PrintValue(constant);
        std::cout << "\n";
        break;
      }
      case OpCode::OP_UNKNOWN:
      {
        std::cout << "unknown opcode\n";
        break;
      }
      case OpCode::OP_RESERVED:
      {
        std::cout << "reserved opcode, doing nothing for now\n";
        break;
      }
      default:
      {
        std::cout << "unknown opcode\n";
        // TODO: what will happen?
      }
    }
  }
}

OpCode VM::IpRead()
{
  return chunk_ptr_->at(ip_++);
}

Value VM::ReadConstant()
{
    size_t address = 0;
    // right now ip_ points to the first byte of constant address just followint OpCode::OP_CONSTANT
    for (size_t idx = 0; idx < Chunk::LEN_SIZE_T; idx++)
    {
      // lval(idx);
      address += static_cast<size_t>(chunk_ptr_->at(idx + ip_)) * pow(256, idx);
      // lval(address);
    }
    ip_ += Chunk::LEN_SIZE_T;
    auto value = chunk_ptr_->constant(address);
    // lmark();
    return value;
}
void VM::PrintValue(Value constant)
{
  std::cout << constant;
}
}
