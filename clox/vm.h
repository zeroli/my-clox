#ifndef CLOX_VM_H_
#define CLOX_VM_H

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;  // instruction pointer
    // stack-based virtual machine
    Value stack[STACK_MAX];
    // pointing to the slot past the last item
    // (points to where the next value to be pushed will go)
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(const char* source);

void push(Value value);
Value pop();

#endif  // CLOX_VM_H_
