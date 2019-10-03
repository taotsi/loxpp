#ifndef COMPILER_HH
#define COMPILER_HH
#include "utility.hh"
#include "chunk.hh"
#include "scanner.hh"
#include "parser.hh"

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
  Parser parser_; // TODO: initialize??

  void advance();
  void error(Token &token, std::string message = "");
  void consume(TokenType token_type, std::string message);

};

} // namespace loxpp

#endif // COMPILER_HH