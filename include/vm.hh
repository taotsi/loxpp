#ifndef VM_HH
#define VM_HH

#include <memory>
#include <vector>
#include <functional>
#include "chunk.hh"
#include "compiler.hh"

namespace loxpp
{

enum class InterpretResult
{
  OK,
  COMPILE_ERROR,
  RUNTIME_ERROR
};

// NOTE: only one VM instance is needed
class VM
{
public:
  VM() {};
  VM(const VM&) = default;
  VM(VM&&) = default;
  VM& operator=(const VM&) = default;
  VM& operator=(VM&&) = default;
  ~VM() = default;

  void repl();
  void run_file(const std::string path);
  InterpretResult interpret(const std::string &src);
  std::string read_file(std::string path);
  inline size_t ip() {return ip_;}

private:
  std::shared_ptr<Chunk> chunk_ptr_;
  size_t ip_ = 0;
  std::vector<Value> stack_;
  Compiler compiler_;

  InterpretResult run();
  OpCode ip_read();
  Value read_constant();
  void print_value(Value constant);
  void push(Value val);
  Value pop();

  template<typename Func>
  void binary_op(Func func)
  {
    auto r = pop();
    auto l = pop();
    push(func(l, r));
  }
};
}

#endif // VM_HH
