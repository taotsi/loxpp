#include "catch.hpp"
#include "vm.hh"
#include "token.hh"
#include "utility.hh"

using namespace taotsi;

TEST_CASE("compiler")
{
  loxpp::VM vm;
  loxpp::Chunk chunk;
  loxpp::Compiler compiler;
#ifdef TEST_SCRIPT_PATH
  auto src = vm.read_file(TEST_SCRIPT_PATH);
  compiler.compile(src, chunk);
#endif
}