#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(chunk->code,
                                 uint8_t,
                                 oldCapacity,
                                 chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

