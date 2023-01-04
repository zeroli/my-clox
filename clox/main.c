#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[])
{
    initVM();

    Chunk chunk;
    initChunk(&chunk);

    // write op `load constant value` to byte code
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_NEGATE, 123);
    // write op `return` to byte code
    writeChunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "test chunk");

    interpret(&chunk);

    freeVM();
    freeChunk(&chunk);

    system("pause");
    return 0;
}
