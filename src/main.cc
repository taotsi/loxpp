#include <stdio.h>
#include "common.hh"
#include "chunk.hh"
#include "debug.hh"

int main(int argc, const char **argv){
  Chunk chunk;
  chunk.Write(OpCode::OP_RETURN);
  chunk.Write(OpCode::OP_UNKNOWN);
  auto pos = chunk.AddConstant(3.14);
  chunk.Write(OpCode::OP_CONSTANT);
  chunk.Write(static_cast<OpCode>(pos));
  Debuger debug;
  debug.Disassemble(chunk, "test");

  printf("~ done ~\n");
  return 0;
}