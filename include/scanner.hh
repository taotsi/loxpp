#ifndef SCANNER_HH
#define SCANNER_HH
#include "utility.hh"
#include "token.hh"

namespace loxpp
{

class Scanner
{
public:
  Scanner() {};
  DEFAULT_SPECIAL_FUNCTIONS(Scanner);
  Token scan_token();
  void load_source(std::string &src);
  std::string token_str(Token &token);

private:
  size_t start_ = 0;    // index of start character of current token
  size_t current_ = 0;  // index of current character ready to be scanned
  size_t line_ = 0;
  std::string src_;

  Token make_token(TokenType token_type);
  Token error_token(std::string msg);
  char advance();
  bool match_tail(char expected);
  void skip_non_token(); // white space, new line, comments and so on
  inline char peek();
  inline char peek_next();
  Token scan_string();
  Token scan_number();
  Token scan_identifier();
  TokenType identifier_type();
  inline std::string current_lexeme();
  TokenType check_keyword(size_t offset,
    std::string tail, TokenType token_type);

  bool is_at_end();
};

} // namespace loxpp


#endif // SCANNER_HH