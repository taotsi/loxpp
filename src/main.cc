#include <stdio.h>
#include "common.hh"
#include "chunk.hh"
#include "debug.hh"

int main(int argc, const char **argv){
  Chunk chunk;
  chunk.Write(OpCode::OP_RETURN);
  chunk.Write(OpCode::OP_UNKNOWN);
  Debuger debug;
  debug.Disassemble(chunk, "test");

  printf("~ done ~\n");
  return 0;
}