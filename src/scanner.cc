#include "scanner.hh"
#include "utility.hh"
#include <unordered_map>
#include <string>
#include <cctype>

namespace loxpp
{

using namespace taotsi;

Token Scanner::scan_token()
{
  skip_non_token();

  start_ = current_;
  auto c = advance();

  if(std::isdigit(c))
  {
    return scan_number();
  }
  if(std::isalpha(c) || c == '_')
  {
    return scan_identifier();
  }

  switch(c)
  {
    case '(':
    {
      return make_token(TokenType::LEFT_PAREN);
    }
    case ')':
    {
      return make_token(TokenType::RIGHT_PAREN);
    }
    case '{':
    {
      return make_token(TokenType::LEFT_BRACE);
    }
    case '}':
    {
      return make_token(TokenType::RIGHT_BRACE);
    }
    case ';':
    {
      return make_token(TokenType::SEMICOLON);
    }
    case ',':
    {
      return make_token(TokenType::COMMA);
    }
    case '.':
    {
      return make_token(TokenType::DOT);
    }
    case '-':
    {
      return make_token(TokenType::MINUS);
    }
    case '+':
    {
      return make_token(TokenType::PLUS);
    }
    case '/':
    {
      return make_token(TokenType::SLASH);
    }
    case '*':
    {
      return make_token(TokenType::STAR);
    }
    case '!':
    {
      return make_token(match_tail('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    }
    case '=':
    {
      return make_token(match_tail('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    }
    case '>':
    {
      return make_token(match_tail('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    }
    case '<':
    {
      return make_token(match_tail('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    }
    case '"':
    {
      return scan_string();
    }
    case '\0':
    {
      return make_token(TokenType::EOF);
    }
  }

  return error_token("unexpected character!");
}

// TODO: maybe I should use a stack, to switch between different files
void Scanner::load_source(std::string &src)
{
  src_ = src;
  start_ = 0;
  current_ = 0;
  line_ = 0;
}

Token Scanner::make_token(TokenType token_type)
{
  return Token{token_type, start_, current_ - start_, line_};
}

Token Scanner::error_token(std::string msg)
{
  return Token{TokenType::ERROR, 0, msg.size(), line_};
}

char Scanner::advance()
{
  return src_[current_++];
}

bool Scanner::match_tail(char expected)
{
  if(src_[current_] == expected)
  {
    current_ ++;
    return true;
  }
  return false;
}

void Scanner::skip_non_token()
{
  while(true)
  {
    auto c = peek();
    switch(c)
    {
      case ' ':
      case '\t':
      case '\r':
      {
        advance();
        break;
      }
      case '\n':
      {
        line_ ++;
        advance();
        break;
      }
      case '/':
      {
        if(peek_next() == '/')
        {
          while(peek() != '\n' && peek() != '\0')
          {
            advance();
          }
        }
        break;
      }
      default:
      {
        return;
      }
    }
  }
}

inline char Scanner::peek()
{
  return src_[current_];
}

inline char Scanner::peek_next()
{
  if(current_ + 1 >= src_.size())
  {
    return '\0';
  }
  return src_[current_+1];
}

Token Scanner::scan_string()
{
  while(peek() != '"' && peek() != '\0')
  {
    if(peek() == '\n')
    {
      line_++;
    }
    advance();
  }
  if(is_at_end())
  {
    return error_token("unterminated string");
  }
  advance();
  return make_token(TokenType::STRING);
}

Token Scanner::scan_number()
{
  while(std::isdigit(peek()))
  {
    advance();
  }
  if(peek() == '.')
  {
    advance();
    while(std::isdigit(peek()))
    {
      advance();
    }
  }
  return make_token(TokenType::NUMBER);
}

Token Scanner::scan_identifier()
{
  while(std::isalnum(peek()) || peek() == '_')
  {
    advance();
  }
  return make_token(identifier_type());
}

TokenType Scanner::identifier_type()
{
  auto lex = current_lexeme();
  switch(lex.front())
  {
    case 'a':
    {
      return check_keyword(1, "nd", TokenType::AND);
    }
    case 'c':
    {
      return check_keyword(1, "lass", TokenType::CLASS);
    }
    case 'e':
    {
      return check_keyword(1, "lse", TokenType::ELSE);
    }
    case 'f':
    {
      auto lex = current_lexeme();
      if(lex.size() > 2)
      {
        switch(lex[1])
        {
          case 'a':
          {
            return check_keyword(2, "lse", TokenType::FALSE);
          }
          case 'o':
          {
            return check_keyword(2, "r", TokenType::FOR);
          }
          case 'u':
          {
            return check_keyword(2, "n", TokenType::FUN);
          }
        }
      }
      break;
    }
    case 'i':
    {
      return check_keyword(1, "f", TokenType::IF);
    }
    case 'n':
    {
      return check_keyword(1, "il", TokenType::NIL);
    }
    case 'o':
    {
      return check_keyword(1, "r", TokenType::OR);
    }
    case 'p':
    {
      return check_keyword(1, "rint", TokenType::PRINT);
    }
    case 'r':
    {
      return check_keyword(1, "eturn", TokenType::RETURN);
    }
    case 's':
    {
      return check_keyword(1, "uper", TokenType::SUPER);
    }
    case 't':
    {
      auto lex = current_lexeme();
      if(lex.size() > 2)
      {
        switch(lex[1])
        {
          case 'h':
          {
            return check_keyword(2, "is", TokenType::THIS);
          }
          case 'r':
          {
            return check_keyword(2, "ue", TokenType::TRUE);
          }
        }
      }
      break;
    }
    case 'v':
    {
      return check_keyword(1, "ar", TokenType::VAR);
    }
    case 'w':
    {
      return check_keyword(1, "hile", TokenType::WHILE);
    }
  }
  return TokenType::IDENTIFIER;
}

inline std::string Scanner::current_lexeme()
{
  return src_.substr(start_, current_ - start_);
}

TokenType Scanner::check_keyword(size_t offset,
  std::string tail, TokenType token_type)
{
  auto lex = current_lexeme();
  if(offset > lex.size())
  {
    return TokenType::IDENTIFIER;
  }
  if(lex.substr(offset) != tail)
  {
    return TokenType::IDENTIFIER;;
  }
  return token_type;
}

bool Scanner::is_at_end()
{
  return current_ >= src_.size();
}

std::string Scanner::token_str(Token &token)
{
  return src_.substr(token.start(), token.length());
}


}