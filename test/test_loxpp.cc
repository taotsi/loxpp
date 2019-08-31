#include "catch.hpp"
#include "vm.hh"
#include "token.hh"
#include "utility.hh"

using namespace taotsi;

TEST_CASE("virtual machin")
{
  loxpp::VM vm;
#ifdef TEST_SCRIPT_PATH
  auto src = vm.read_file(TEST_SCRIPT_PATH);
  REQUIRE(src == std::string("print 42"));
#endif
}

TEST_CASE("token")
{
  REQUIRE(loxpp::token_type_name(loxpp::TokenType::EOF) == "EOF");
}