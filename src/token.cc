#include "token.hh"
#include "unordered_map"
#include <tuple>
#include <iomanip>

namespace loxpp
{

std::string token_type_name(TokenType token_type)
{
  static std::unordered_map<TokenType, std::string> token_type_map{
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},
    {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},
    {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::DOT, "DOT"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::SLASH, "SLASH"},
    {TokenType::STAR, "STAR"},

    {TokenType::BANG, "BANG"},
    {TokenType::BANG_EQUAL, "BANG_EQUAL"},
    {TokenType::EQUAL, "EQUAL"},
    {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
    {TokenType::GREATER, "GREATER"},
    {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
    {TokenType::LESS, "LESS"},
    {TokenType::LESS_EQUAL, "LESS_EQUAL"},

    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::STRING, "STRING"},
    {TokenType::NUMBER, "NUMBER"},

    {TokenType::AND, "AND"},
    {TokenType::CLASS, "CLASS"},
    {TokenType::ELSE, "ELSE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::FOR, "FOR"},
    {TokenType::FUN, "FUN"},
    {TokenType::IF, "IF"},
    {TokenType::NIL, "NIL"},
    {TokenType::OR, "OR"},
    {TokenType::PRINT, "PRINT"},
    {TokenType::RETURN, "RETURN"},
    {TokenType::SUPER, "SUPER"},
    {TokenType::THIS, "THIS"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::VAR, "VAR"},
    {TokenType::WHILE, "WHILE"},

    {TokenType::ERROR, "ERROR"},
    {TokenType::EOF, "EOF"}
  };
  return token_type_map[token_type];
}

std::ostream& operator<<(std::ostream &os, TokenType token_type)
{
  os << token_type_name(token_type);
  return os;
}

bool operator==(const Token &lhs, const Token &rhs)
{
  return std::tie(lhs.type_, lhs.start_, lhs.length_, lhs.line_)
      == std::tie(rhs.type_, rhs.start_, rhs.length_, rhs.line_);
}

std::ostream& operator<<(std::ostream &os, Token token)
{
  os << std::setw(14) << token.type_ << ", " << std::setw(4) << token.start_ << " |<-" << token.length_ << "->|  @" << " " << token.line_;
  return os;
}

} // namespace loxpp
