#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

// chunk means a sequence of byte code
typedef struct {
    int count;
    int capacity;
    uint8_t* code;  // byte code array
    int* lines;  // source code lines
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);

// return the index of this value written in array of constants
int addConstant(Chunk* chunk, Value value);

#endif  // CLOX_CHUNK_H_
