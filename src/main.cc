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
    vm.Repl();
  }
  else if(argc == 2)
  {
    vm.RunFile(argv[1]);
  }
  else
  {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  // auto chunk = std::make_shared<Chunk>();
  // auto addr = chunk->AddConstant(1.3);
  // chunk->Write(OpCode::OP_CONSTANT, 2);
  // chunk->Write(addr, 2);
  // addr = chunk->AddConstant(2.4);
  // chunk->Write(OpCode::OP_CONSTANT, 2);
  // chunk->Write(addr, 2);
  // chunk->Write(OpCode::OP_ADD, 2);
  // addr = chunk->AddConstant(5.6);
  // chunk->Write(OpCode::OP_CONSTANT, 2);
  // chunk->Write(addr, 2);
  // chunk->Write(OpCode::OP_DIVIDE, 2);
  // chunk->Write(OpCode::OP_NEGATE, 2);
  // chunk->Write(OpCode::OP_RETURN, 3);
  // if(show_asm)
  // {
  //   Debuger debug;
  //   debug.Disassemble(*chunk, "debug");
  //   std::cout << std::endl;
  // }
  // vm.Interpret(chunk);

  // printf("~ done ~\n");
  return 0;
}