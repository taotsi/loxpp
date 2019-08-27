#include <stdio.h>
#include <string>
#include <experimental/filesystem>
#include "common.hh"
#include "chunk.hh"
#include "debuger.hh"
#include "vm.hh"
#include "utility.hh"

using namespace loxpp;
using namespace taotsi;
// using fs = std::experimental::filesystem;

int main(int argc, const char **argv){
  VM vm;

  if(argc == 1)
  {
    vm.repl();
  }
  else if(argc == 2)
  {
    vm.run_file(argv[1]);
  }
  else
  {
    twarn("Usage: clox [path]");
    exit(64);
  }

  // vm.Interpret(chunk);

  return 0;
}