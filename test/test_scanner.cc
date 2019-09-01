#include "catch.hpp"
#include "vm.hh"
#include "token.hh"
#include "utility.hh"

using namespace taotsi;

TEST_CASE("scanner")
{
  loxpp::Scanner scanner;

  SECTION("single character")
  {
    std::string src1{"{}"};
    scanner.load_source(src1);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_BRACE, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_BRACE, 1, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 2, 1, 0});
  }

  SECTION("double character")
  {
    std::string src2{"!>="};
    scanner.load_source(src2);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::BANG, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::GREATER_EQUAL, 1, 2, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 3, 1, 0});
  }

  SECTION("white space")
  {
    std::string src3{"{  \n}"};
    scanner.load_source(src3);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_BRACE, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_BRACE, 4, 1, 1});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 5, 1, 1});
  }

  SECTION("comments")
  {
    std::string src4{"{//  \n}"};
    scanner.load_source(src4);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_BRACE, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_BRACE, 6, 1, 1});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 7, 1, 1});
  }

  SECTION("literal string")
  {
    std::string src5{"{\"abc\"}"};
    scanner.load_source(src5);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_BRACE, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::STRING, 1, 5, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_BRACE, 6, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 7, 1, 0});
  }

  SECTION("number")
  {
    std::string src6{"{3.14}"};
    scanner.load_source(src6);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_BRACE, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::NUMBER, 1, 4, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_BRACE, 5, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 6, 1, 0});
  }

  SECTION("identifier")
  {
    std::string src7{"x cle"};
    scanner.load_source(src7);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::IDENTIFIER, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::IDENTIFIER, 2, 3, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 5, 1, 0});
  }

  SECTION("keyword, single branch")
  {
    std::string src8{"{class}"};
    scanner.load_source(src8);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_BRACE, 0, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::CLASS, 1, 5, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_BRACE, 6, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 7, 1, 0});
  }

  SECTION("keyword, multiple branch")
  {
    std::string src9{"for true"};
    scanner.load_source(src9);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::FOR, 0, 3, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::TRUE, 4, 4, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EOF, 8, 1, 0});
  }

  SECTION("all together")
  {
#ifdef TEST_SCRIPT_PATH
    loxpp::VM vm;
    auto src10 = vm.read_file(TEST_SCRIPT_PATH);
    scanner.load_source(src10);
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::IF, 0, 2, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_PAREN, 2,1 , 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::IDENTIFIER, 3, 4, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EQUAL_EQUAL, 8, 2, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::TRUE, 11, 4, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::AND, 16, 3, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::IDENTIFIER, 20, 2, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::GREATER, 23, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::NUMBER, 25, 2, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_PAREN, 27, 1, 0});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::LEFT_BRACE, 29, 1, 1});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::PRINT, 33, 5, 2});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::STRING, 39, 5, 2});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::SEMICOLON, 44, 1, 2});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::VAR, 48, 3, 3});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::IDENTIFIER, 52, 2, 3});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::EQUAL, 55, 1, 3});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::NUMBER, 57, 2, 3});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::SEMICOLON, 59, 1, 3});
    REQUIRE(scanner.scan_token() == loxpp::Token{loxpp::TokenType::RIGHT_BRACE, 61, 1, 4});
#endif
  }
}