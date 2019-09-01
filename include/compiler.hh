#ifndef COMPILER_HH
#define COMPILER_HH
#include "utility.hh"
#include "chunk.hh"
#include "scanner.hh"

namespace loxpp
{
enum class InterpretResult
{
  OK,
  COMPILE_ERROR,
  RUNTIME_ERROR
};

class Compiler
{
public:
  Compiler() {};
  DEFAULT_SPECIAL_FUNCTIONS(Compiler);
  bool compile(std::string &src, Chunk &chunk);

private:
  Scanner scanner_;
};

} // namespace loxpp

#endif // COMPILER_HH