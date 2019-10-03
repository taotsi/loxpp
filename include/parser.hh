#ifndef PARSER_HH
#define PARSER_HH
#include "utility.hh"
#include "token.hh"

namespace loxpp
{

class Parser
{
public:
  Parser() {};
  DEFAULT_SPECIAL_FUNCTIONS(Parser);

  Token current_;
  Token previous_;
  bool had_error_ = false;
  bool panic_mode_ = false;
};

} // namespace loxpp


#endif // PARSER_HH