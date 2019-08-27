#include "catch.hpp"
#include "vm.hh"
#include "utility.hh"

using namespace loxpp;
using namespace taotsi;

TEST_CASE("virtual machin")
{
  VM vm;
#ifdef TEST_SCRIPT_PATH
  auto src = vm.read_file(TEST_SCRIPT_PATH);
  REQUIRE(src == std::string("print 42"));
#endif
}