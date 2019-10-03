#include "compiler.hh"
#include <iomanip>

namespace loxpp
{

bool Compiler::compile(std::string &src, Chunk &chunk)
{
  scanner_.load_source(src);
  advance();
  expression(); // TODO:
  consume(TokenType::EOF, "Expect end of expression.");
  return !parser_.had_error_;
}

void Compiler::advance()
{
  parser_.previous_ = parser_.current_;
  while(true)
  {
    parser_.current_ = scanner_.scan_token();

    if(parser_.current_.type() != TokenType::ERROR)
    {
      break;
    }

    error(parser_.current_);
  }
}

void Compiler::error(Token &token, std::string message)
{
  if(parser_.panic_mode_)
  {
    return;
  }
  parser_.panic_mode_ = true;

  std::cerr << "[line " << token.line() << "] Error";
  if(token.type() == TokenType::EOF)
  {
    std::cerr << " at end";
  }
  else if(token.type() == TokenType::ERROR)
  {

  }
  else
  {
    std::cerr << "at " << scanner_.token_str(token);
  }
  std::cerr << ": " << message << "\n";
  parser_.had_error_ = true;
}

void Compiler::consume(TokenType token_type, std::string message)
{
  if(parser_.current_.type() == token_type)
  {
    advance();
    return;
  }
  error(parser_.current_, message);
}

}