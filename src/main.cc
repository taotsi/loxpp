#include <stdio.h>
#include "CLI/CLI.hpp"
#include "common.hh"
#include "chunk.hh"
#include "debuger.hh"
#include "vm.hh"

using namespace loxpp;

int main(int argc, const char **argv){
  bool show_asm = false;
  // bool only_debug = false;

  CLI::App arg_parser("main arg parser");
  arg_parser.add_flag("-d", show_asm, "show assemble code");
  CLI11_PARSE(arg_parser, argc, argv);
  VM vm;
  auto chunk = std::make_shared<Chunk>();
  // chunk->Write(OpCode::OP_UNKNOWN, 1);

  auto addr = chunk->AddConstant(1.3);
  chunk->Write(OpCode::OP_CONSTANT, 2);
  chunk->Write(addr, 2);

  addr = chunk->AddConstant(2.4);
  chunk->Write(OpCode::OP_CONSTANT, 2);
  chunk->Write(addr, 2);

  chunk->Write(OpCode::OP_ADD, 2);

  addr = chunk->AddConstant(5.6);
  chunk->Write(OpCode::OP_CONSTANT, 2);
  chunk->Write(addr, 2);

  chunk->Write(OpCode::OP_DIVIDE, 2);

  chunk->Write(OpCode::OP_NEGATE, 2);

  chunk->Write(OpCode::OP_RETURN, 3);

  if(show_asm)
  {
    Debuger debug;
    debug.Disassemble(*chunk, "debug");
    std::cout << std::endl;
  }

  vm.Interpret(chunk);

  // printf("~ done ~\n");
  return 0;
}