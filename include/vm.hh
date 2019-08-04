#ifndef VM_HH
#define VM_HH

#include <memory>
#include <vector>
#include <functional>
#include "chunk.hh"

namespace loxpp
{

enum class InterpretResult
{
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
};

// NOTE: only one VM instance is needed
class VM
{
public:
  VM();
  // VM(std::shared_ptr<Chunk>);
  VM(const VM&) = default;
  VM(VM&&) = default;
  VM& operator=(const VM&) = default;
  VM& operator=(VM&&) = default;
  ~VM() = default;

  // InterpretResult Interpret();
  InterpretResult Interpret(std::shared_ptr<Chunk> Chunk);
  inline size_t ip() {return ip_;}

private:
  std::shared_ptr<Chunk> chunk_ptr_;
  size_t ip_ = 0;
  std::vector<Value> stack_;

  InterpretResult Run();
  OpCode IpRead();
  Value ReadConstant();
  void PrintValue(Value constant);
  void Push(Value val);
  Value Pop();

  template<typename Func>
  void BinaryOp(Func func)
  {
    auto r = Pop();
    auto l = Pop();
    Push(func(l, r));
  }
};
}

#endif // VM_HH
