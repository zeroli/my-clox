#ifndef CLOX_DEBUG_H_
#define CLOX_DEBUG_H_

#include "chunk.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name);
// return offset of next instruction
int disassembleInstruction(Chunk* chunk, int offset);

#endif  // CLOX_DEBUG_H_
