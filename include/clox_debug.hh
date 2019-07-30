#ifndef CLOX_DEBUG_HH
#define CLOX_DEBUG_HH

#include "clox_chunk.hh"

void DisassembleChunk(Chunk *chunk, const char* name);
int DisassembleInstruction(Chunk *chunk, int offset);
int simpleInstruction(const char* name, int offset);

#endif // CLOX_DEBUG_HH
