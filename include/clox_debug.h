#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#include "clox_chunk.h"

void DisassembleChunk(Chunk *chunk, const char* name);
int DisassembleInstruction(Chunk *chunk, int offset);
int simpleInstruction(const char* name, int offset);

#endif // CLOX_DEBUG_H
