#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "msg.hh"
#include "vm.hh"
#include "debuger.hh"
#include "utility.hh"

// #define DEBUG_TRACE_EXECUTION

namespace loxpp
{

using namespace taotsi;

VM::VM()
{

}
// VM::VM(std::shared_ptr<Chunk> chunk)
//   : chunk_ptr_{chunk}
// {

// }

void VM::Repl()
{
  tmsg("VM::Repl");
  std::string line;
  std::cout << "> ";
  while(std::getline(std::cin, line))
  {
    if(!line.empty())
    {
      // auto chunk = std::make_shared<Chunk>(ReadLine(line));
      // Interpret(chunk);
    }
    std::cout << "> ";
  }
}

void VM::RunFile(const std::string path)
{
  // auto chunk = std::make_shared<Chunk>(ReadFile(path));
  // Interpret(chunk);
}

InterpretResult VM::Interpret(std::shared_ptr<Chunk> chunk)
{
  chunk_ptr_ = chunk;
  ip_ = 0;
  return Run();
}

Chunk VM::ReadLine(std::string line)
{
  // TODO:
  return Chunk{};
}

Chunk VM::ReadFile(std::string path)
{
  // TODO:
  return Chunk{};
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
    OpCode instruct = IpRead();
    // tval(ip_);
    // tval(chunk_ptr_->size());
    switch(instruct)
    {
      case OpCode::OP_RETURN:
      {
        std::cout << Pop() << "\n";
        return InterpretResult::INTERPRET_OK;
      }
      case OpCode::OP_CONSTANT:
      {
        Value constant = ReadConstant();
        Push(constant);
        PrintValue(constant);
        // tval(stack_.back());
        break;
      }
      case OpCode::OP_UNKNOWN:
      {
        std::cout << "unknown opcode, maybe forgot to resolve some opcode?\n";
        break;
      }
      case OpCode::OP_RESERVED:
      {
        // std::cout << "reserved opcode\n";
        break;
      }
      case OpCode::OP_NEGATE:
      {
        Push(-Pop());
        break;
      }
      case OpCode::OP_ADD:
      {
        // Implicit instantiation for template function, super cool
        BinaryOp([](Value l, Value r){return l + r;});
        break;
      }
      case OpCode::OP_SUBTRACT:
      {
        BinaryOp([](Value l, Value r){return l - r;});
        break;
      }
      case OpCode::OP_MULTIPLY:
      {
        BinaryOp([](Value l, Value r){return l * r;});
        break;
      }
      case OpCode::OP_DIVIDE:
      {
        BinaryOp([](Value l, Value r){return l / r;});
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
  // lmark();
  size_t address = 0;
  // right now ip_ points to the first byte of constant address just followint OpCode::OP_CONSTANT
  // TODO: this is repeated code block, should be reusable
  for (size_t idx = 0; idx < Chunk::LEN_SIZE_T; idx++)
  {
    // tval(idx);
    address |= static_cast<size_t>(chunk_ptr_->at(idx + ip_)) << 8*(Chunk::LEN_SIZE_T - idx - 1);
    // tval(address);
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
