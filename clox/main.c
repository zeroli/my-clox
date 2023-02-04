#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void writeExpr1(Chunk* chunk)
{   // expression: 1 * 2 + 3
    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 1), 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 2), 123);

    writeChunk(chunk, OP_MULTIPLY, 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 3), 123);

    writeChunk(chunk, OP_ADD, 123);
    // write op `return` to byte code
    writeChunk(chunk, OP_RETURN, 123);
}

static void writeExpr2(Chunk* chunk)
{  // expression: 1 + 2 * 3
    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 2), 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 3), 123);

    writeChunk(chunk, OP_MULTIPLY, 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 1), 123);

    writeChunk(chunk, OP_ADD, 123);

    // write op `return` to byte code
    writeChunk(chunk, OP_RETURN, 123);
}

static void writeExpr3(Chunk* chunk)
{   // expression: 3 - 2 - 1
    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 3), 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 2), 123);

    writeChunk(chunk, OP_SUBTRACT, 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 1), 123);

    writeChunk(chunk, OP_SUBTRACT, 123);

    writeChunk(chunk, OP_RETURN, 123);
}

static void writeExpr4(Chunk* chunk)
{   // expression: 1 + 2 * 3 - 4 / -5
    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 1), 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 2), 123);
    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 3), 123);
    writeChunk(chunk, OP_MULTIPLY, 123);
    writeChunk(chunk, OP_ADD, 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 4), 123);

    writeChunk(chunk, OP_CONSTANT, 123);
    writeChunk(chunk, addConstant(chunk, 5), 123);
    writeChunk(chunk, OP_NEGATE, 123);

    writeChunk(chunk, OP_DIVIDE, 123);
    writeChunk(chunk, OP_SUBTRACT, 123);

    writeChunk(chunk, OP_RETURN, 123);
}

// read - evaluate - print - loop
static void repl()
{
    char line[1024];
    for (; ;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

static char* readFile(const char* path)
{
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    // make one more room for null byte
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read %s\n", path);
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file %s\n", path);
        exit(74);
    }
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(const char* path)
{
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) {
        exit(65);
    }
    if (result == INTERPRET_RUNTIME_ERROR) {
        exit(70);
    }
}

int main(int argc, const char* argv[])
{
    printf("clox - vm-based interpreter...\n");

    initVM();

    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    Chunk chunk;
    initChunk(&chunk);

    // write op `load constant value` to byte code
    writeExpr1(&chunk);
    writeExpr2(&chunk);
    writeExpr3(&chunk);
    writeExpr4(&chunk);

    // expression: -((1.2 + 3.4) / 5.6)
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIVIDE, 123);
    writeChunk(&chunk, OP_NEGATE, 123);
    // write op `return` to byte code
    writeChunk(&chunk, OP_RETURN, 123);

    writeChunk(&chunk, OP_EXIT, 124);

    disassembleChunk(&chunk, "test chunk");

    //interpret(&chunk);

    freeVM();
    freeChunk(&chunk);

    system("pause");
    return 0;
}
