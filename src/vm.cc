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
    std::cout << "stack: ";
    if(!stack_.empty())
    {
      auto size_stack = stack_.size();
      for (size_t slot = 0; slot < size_stack; slot++)
      {
        std::cout << "[" << stack_[slot] << "] ";
      }
    }
    else
    {
      std::cout << "empty";
    }
    std::cout << "\n";
#endif
    OpCode instruct;
    switch(instruct = IpRead())
    {
      case OpCode::OP_RETURN:
      {
        std::cout << Pop() << "\n";
        return InterpretResult::INTERPRET_OK;
      }
      case OpCode::OP_CONSTANT:
      {
        Value constant = ReadConstant();
        // lmark();
        Push(constant);
        // PrintValue(constant);
        break;
      }
      case OpCode::OP_UNKNOWN:
      {
        std::cout << "unknown opcode\n";
        break;
      }
      case OpCode::OP_RESERVED:
      {
        std::cout << "reserved opcode\n";
        break;
      }
      case OpCode::OP_NEGATE:
      {
        Push(-Pop());
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
    // TODO: this is repeated code block, should be reusable
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
  std::cout << constant << "\n";
}
void VM::Push(Value val)
{
  stack_.push_back(val);
}
Value VM::Pop()
{
  auto val = stack_.back();
  stack_.pop_back();
  return val;
}

}
