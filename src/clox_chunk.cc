#include <stdio.h>
#include "clox_chunk.hh"
#include "clox_memory.hh"

void InitChunk(Chunk *chunk){
  chunk->capacity = 0;
  chunk->count = 0;
  chunk->code = NULL;
}

void FreeChunk(Chunk *chunk){
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  InitChunk(chunk);
}

void WriteChunk(Chunk *chunk, uint8_t byte){
  if(chunk->capacity < chunk->count+1){
    int old_capacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(old_capacity);
    chunk->code = GROW_ARRAY(chunk->code, uint8_t,
      old_capacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->count++;
}