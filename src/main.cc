#include <stdio.h>
#include "common.hh"
#include "chunk.hh"
#include "debuger.hh"
#include "vm.hh"

using namespace loxpp;

int main(int argc, const char **argv){
  bool with_debug = false;
  bool only_debug = false;

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

  // Debuger debug;
  // debug.Disassemble(*chunk, "debug");

  vm.Interpret(chunk);

  // printf("~ done ~\n");
  return 0;
}