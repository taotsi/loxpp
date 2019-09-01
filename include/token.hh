#ifndef HH
#define HH

#include <string>
#include "utility.hh"

namespace loxpp
{

enum class TokenType
{
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN,
  LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS,
  SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE,
  FOR, FUN, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS,
  TRUE, VAR, WHILE,

  ERROR,

#undef EOF
  EOF
};

std::string token_type_name(TokenType token_type);
std::ostream& operator<<(std::ostream &os, TokenType token_type);

class Token
{
public:
  Token() {};
  Token(TokenType token_type, size_t start, size_t length, size_t line)
    : type_{token_type}, start_{start}, length_{length}, line_{line}
  {}
  DEFAULT_SPECIAL_FUNCTIONS(Token);
  inline TokenType type() const { return type_; }
  inline size_t line() const { return line_; }
  inline size_t start() const { return start_; }
  inline size_t lenght() const { return length_; }
  friend bool operator==(const Token &lhs, const Token &rhs);
  friend std::ostream& operator<<(std::ostream &os, Token token);
private:
  TokenType type_;
  size_t start_ = 0;
  size_t length_ = 0;
  size_t line_ = 0; // TODO: should be a range, not a single value

};

}

#endif // HH