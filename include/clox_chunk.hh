#ifndef CLOX_CHUNK_HH
#define CLOX_CHUNK_HH

#include "clox_common.hh"

typedef enum{
  OP_RETURN,
}OpCode;

typedef struct{
  int count;
  int capacity;
  uint8_t* code;
}Chunk;

void InitChunk(Chunk *chunk);
void FreeChunk(Chunk *chunk);
void WriteChunk(Chunk *chunk, uint8_t byte);

#endif // CLOX_CHUNK_HH