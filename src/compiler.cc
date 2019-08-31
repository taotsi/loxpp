#include "compiler.hh"

namespace loxpp
{

Chunk Compiler::compile(const std::string &src)
{
  while(true)
  {
    auto token = scanner_.scan_token();
    if(token.type() == TokenType::TOKEN_EOF)
    {
      break;
    }
  }
  return Chunk{};
}

}