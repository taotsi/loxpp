#include "compiler.hh"
#include <iomanip>

namespace loxpp
{

bool Compiler::compile(std::string &src, Chunk &chunk)
{
  size_t line = -1;
  scanner_.load_source(src);
  while(true)
  {
    auto token = scanner_.scan_token();
    if(token.line() != line)
    {
      std::cout << std::setw(4) << token.line() << "-";
      line = token.line();
    }
    else
    {
      std::cout << "   | ";
    }
    std::cout << token << "\n";
    if(token.type() == TokenType::EOF)
    {
      break;
    }
  }
  return false;
}

}