#ifndef CLOX_COMPILER_H_
#define CLOX_COMPILER_H_

#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif  // CLOX_COMPILER_H_
