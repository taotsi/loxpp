#include <stdio.h>
#include "clox_common.hh"
#include "clox_chunk.hh"
#include "clox_debug.hh"

int main(int argc, const char **argv){
  Chunk chunk;
  InitChunk(&chunk);
  WriteChunk(&chunk, OP_RETURN);
  DisassembleChunk(&chunk, "chunk test");
  FreeChunk(&chunk);
  printf("~ done ~\n");
  return 0;
}