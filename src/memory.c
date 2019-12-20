#include <stdlib.h>

#include "common.h"
#include "compiler.h"
#include "memory.h"
#include "vm.h"

#ifdef DEBUG_LOG_GC
#include <stdio.h>
#include "debug.h"
#endif

void* reallocate(void* previous,
                 size_t oldSize,
                 size_t newSize) {
    if (newSize > oldSize) {
#ifdef DEBUG_STRESS_GC
        collectGarbage();
#endif
    }
    
    if (newSize == 0) {
        free(previous);
        return NULL;
    }

    return realloc(previous, newSize);
}

void markObject(Obj* object) {
    if (object == NULL) return;

#ifdef DEBUG_LOG_GC
    printf("%p mark ", (void*) object);
    printValue(OBJ_VAL(object));
    printf("\n");
#endif
    
    object->isMarked = true;
}

void markValue(Value value) {
    if (!IS_OBJ(value)) return;
    markObject(AS_OBJ(value));
}

static void freeObject(Obj* object) {
#ifdef DEBUG_LOG_GC
    printf("%p free type %d\n", (void*) object, object->type);
#endif
    
    switch (object->type) {
    case OBJ_STRING: {
        ObjString* string = (ObjString*)object;
        FREE_ARRAY(char, string->chars, string->length + 1);
        FREE(ObjString, object);
        break;
    }

    case OBJ_UPVALUE: {
        FREE(ObjUpvalue, object);
        break;
    }

    case OBJ_NATIVE: {
        FREE(ObjNative, object);
        break;
    }

    case OBJ_CLOSURE: {
        ObjClosure* closure = (ObjClosure*) object;
        FREE_ARRAY(ObjUpvalue*, closure->upvalues, closure->upvalueCount);
        FREE(ObjClosure, object);
        break;
    }

    case OBJ_FUNCTION: {
        ObjFunction* function = (ObjFunction*)object;
        freeChunk(&function->chunk);
        FREE(ObjFunction, object);
        break;
    }
    }
}

static void markRoots() {
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
        markValue(*slot);
    }

    for (int i = 0; i < vm.frameCount; i++) {
        markObject((Obj*) vm.frames[i].closure);
    }

    for (ObjUpvalue* upvalue = vm.openUpvalues;
         upvalue != NULL;
         upvalue = upvalue->next) {
        markObject((Obj*) upvalue);
    }

    markTable(&vm.globals);

    markCompilerRoots();
}

void collectGarbage() {
#ifdef DEBUG_LOG_GC
    printf("-- gc begin\n");
#endif

    markRoots();

#ifdef DEBUG_LOG_GC
    printf("-- gc end\n");
#endif
}

void freeObjects() {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }
}

