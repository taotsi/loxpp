#include <stdio.h>
#include "common.hh"
#include "chunk.hh"
#include "debug.hh"

int main(int argc, const char **argv){
  Chunk8 chunk;
  chunk.Write(OpCode::OP_RETURN);
  // DisassembleChunk(&chunk, "chunk test");

  printf("~ done ~\n");
  return 0;
}