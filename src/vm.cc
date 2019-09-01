#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>
#include "msg.hh"
#include "vm.hh"
#include "debuger.hh"
#include "utility.hh"

// #define DEBUG_TRACE_EXECUTION

namespace loxpp
{

using namespace taotsi;

void VM::repl()
{
  std::string line;
  std::cout << "> ";
  while(std::getline(std::cin, line))
  {
    if(!line.empty())
    {
      interpret(line);
    }
    std::cout << "> ";
  }
}

void VM::run_file(const std::string path)
{
  auto src = read_file(path);
  auto interpret_result = interpret(src);

  if(interpret_result == InterpretResult::COMPILE_ERROR)
  {
    exit(65);
  }
  if(interpret_result == InterpretResult::RUNTIME_ERROR)
  {
    exit(70);
  }
}

InterpretResult VM::interpret(std::string &src)
{
  compiler_.compile(src);
  return run();
}

std::string VM::read_file(std::string path)
{
  std::ifstream of{path};
  if(!of.is_open())
  {
    terr("Cound not open file ", path);
    exit(74);
  }
  std::string source;
  of.seekg(0, std::ios::end);
  source.resize(of.tellg());
  of.seekg(0, std::ios::beg);
  of.read(source.data(), source.size());
  of.close();

  return source;
}

InterpretResult VM::run()
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
    OpCode instruct = ip_read();
    // tval(ip_);
    // tval(chunk_ptr_->size());
    switch(instruct)
    {
      case OpCode::OP_RETURN:
      {
        std::cout << pop() << "\n";
        return InterpretResult::OK;
      }
      case OpCode::OP_CONSTANT:
      {
        Value constant = read_constant();
        push(constant);
        print_value(constant);
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
        push(-pop());
        break;
      }
      case OpCode::OP_ADD:
      {
        // Implicit instantiation for template function, super cool
        binary_op([](Value l, Value r){return l + r;});
        break;
      }
      case OpCode::OP_SUBTRACT:
      {
        binary_op([](Value l, Value r){return l - r;});
        break;
      }
      case OpCode::OP_MULTIPLY:
      {
        binary_op([](Value l, Value r){return l * r;});
        break;
      }
      case OpCode::OP_DIVIDE:
      {
        binary_op([](Value l, Value r){return l / r;});
        break;
      }
      default:
      {
        std::cout << "unknown opcode\n";
      }
    }
  }
  return InterpretResult::OK; // TEMP:
}

OpCode VM::ip_read()
{
  return chunk_ptr_->at(ip_++);
}

Value VM::read_constant()
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
void VM::print_value(Value constant)
{
  std::cout << constant << "\n";
}
void VM::push(Value val)
{
  stack_.push_back(val);
}
Value VM::pop()
{
  auto val = stack_.back();
  stack_.pop_back();
  return val;
}

}
