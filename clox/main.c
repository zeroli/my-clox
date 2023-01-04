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

int main(int argc, const char* argv[])
{
    initVM();

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

    interpret(&chunk);

    freeVM();
    freeChunk(&chunk);

    system("pause");
    return 0;
}
