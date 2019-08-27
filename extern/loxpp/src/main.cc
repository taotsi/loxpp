#include <stdio.h>
#include <string>
#include <experimental/filesystem>
#include "CLI/CLI.hpp"
#include "common.hh"
#include "chunk.hh"
#include "debuger.hh"
#include "vm.hh"

using namespace loxpp;
// using fs = std::experimental::filesystem;

int main(int argc, const char **argv){

  bool show_asm = false;
  std::string file_path;

  // CLI::App arg_parser("main arg parser");
  // arg_parser.add_flag("-d", show_asm, "show assemble code");
  // arg_parser.add_option("-f, --file", file_path, "path of file to run");
  // CLI11_PARSE(arg_parser, argc, argv);

  // if(file_path.empty())
  // {
  //   // TODO: repl
  //   tmsg("empty path");
  // }
  // else
  // {
  //   // TODO: run file
  //   tmsg("not empty path");
  // }

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
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  // vm.Interpret(chunk);

  return 0;
}