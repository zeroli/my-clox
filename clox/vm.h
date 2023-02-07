#ifndef CLOX_VM_H_
#define CLOX_VM_H_

#include "chunk.h"
#include "value.h"
#include "object.h"
#include "table.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;  // instruction pointer
    // stack-based virtual machine
    Value stack[STACK_MAX];
    // pointing to the slot past the last item
    // (points to where the next value to be pushed will go)
    Value* stackTop;
    Table globals;  // global variables
    Table strings;  // intern strings
    Obj* objects;  // all objects allocated
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();

InterpretResult interpret(const char* source);

void push(Value value);
Value pop();

#endif  // CLOX_VM_H_
