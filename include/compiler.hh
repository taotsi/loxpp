#ifndef COMPILER_HH
#define COMPILER_HH
#include "utility.hh"
#include "chunk.hh"
#include "scanner.hh"

namespace loxpp
{

class Compiler
{
public:
  Compiler() {};
  DEFAULT_SPECIAL_FUNCTIONS(Compiler);
  Chunk compile(std::string &src);

private:
  Scanner scanner_;
};

} // namespace loxpp

#endif // COMPILER_HH