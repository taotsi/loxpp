#include <stdio.h>
#include "clox_common.h"
#include "clox_chunk.h"
#include "clox_debug.h"

int main(int argc, const char **argv){
  Chunk chunk;
  InitChunk(&chunk);
  WriteChunk(&chunk, OP_RETURN);
  DisassembleChunk(&chunk, "chunk test");
  FreeChunk(&chunk);
  printf("~ done ~\n");
  return 0;
}