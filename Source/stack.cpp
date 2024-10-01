#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "stackdef.h"

static const int Mask = rand();
template <typename T>
inline T val (T value) { return StackCheck(value); }
#define     val( value )        ( value )

#define verified  || val(src)

#define Max(x, y) (x) > (y) ? (x) : (y)

FILE *flog = fopen("Stack.log", "w");

StackError StackCtor (Stack *src, size_t length){

    src->src = (type *) calloc (1, length * sizeof(type) + 2*Cansize);
    memcpy(src->src, Can, Cansize);

    if (src->src == NULL) return EMPTY_SOURCE;

    src->size = length;
    memcpy(((char*) (src->src + length)) + Cansize, Can, Cansize);

    src->pointer = 0;
    src->info = {"stack.cpp", Hash(src->src, src->src+src->size), "src"};

    STACK_ASSERT(*src);
    return StackCheck(src);
}

StackError StackDtor(Stack *src){
    STACK_ASSERT(*src);

    free(src->src);
    src->pointer = 0;
    src->size = 0;

    STACK_ASSERT(*src);
    return StackCheck(src);
}

StackError StackPush (Stack *src, type elem){
    STACK_ASSERT(*src);

    if (src->pointer == src->size - 1) {
        Resize(src, src->size * 2, src->size) verified;
    }

    ((type*) ((char*) src->src + Cansize))[src->pointer] = elem;
    src->pointer++;

    src->info = {"stack.cpp", Hash(src->src, src->src+src->size), "src"};

    STACK_ASSERT(*src);
    return StackCheck(src);
}


StackError Resize(Stack *src, size_t size, size_t lastsize) {
    STACK_ASSERT(*src);

    src->size =  Max(size, DefaultSize);

    type *buf = (type*) realloc (src->src, src->size*sizeof(type) + 2*Cansize);
    if (!buf) return EMPTY_STACK;

    memset(((char *) (buf + lastsize)) + Cansize, '\0', Cansize);
    src->src = buf;

    memcpy((char*)(src->src + src->size) + Cansize, Can, Cansize);
    src->info = {"stack.cpp", Hash(src->src, src->src+src->size), "src"};

    DUMP(*src);
    STACK_ASSERT(*src);
    return StackCheck(src);
}


StackError StackPop (Stack *src, type *elem){
    STACK_ASSERT(*src);

    src->pointer--;
    *elem = ((type*) ((char*) src->src + Cansize))[src->pointer];
    ((type*) ((char*) src->src + Cansize))[src->pointer] = 0;

    src->info = {"stack.cpp", Hash(src->src, src->src+src->size), "src"};

    if (src->pointer <= src->size / 4 && src->size > DefaultSize){
        Resize(src, src->size/2, src->size) verified;
    }

    src->info = {"stack.cpp", Hash(src->src, src->src+src->size), "src"};

    STACK_ASSERT(*src);
    return StackCheck(src);
}

StackError StackCheck (Stack *src) {

    if (src == NULL)                return EMPTY_STACK   ;
    if (src->src == NULL)           return EMPTY_SOURCE  ;
    if (src->pointer > src->size && src->size != 0)  return STACK_OVERFLOW;
    if (memcmp((src->src), Can, Cansize) ||
        memcmp((char *) (src->src + src->size) + Cansize, Can, Cansize)) {
        return LAZHA;}
    if (Hash(src->src, src->src+src->size) != src->info.line) return POPALSYA_NA_HASHE;
    return OK;
}
StackError StackDump(Stack *src, const char *file, const int line, const char *errname) {

    fprintf(flog, "Dump from %s:%d\n", file, line);

    fprintf(flog, "Error type: %s\n", errname);
    if (src->src != NULL){
        for (size_t i = 0; i < Cansize; i++){
                fprintf(flog, "[%c]", *((char*)src->src + i));
        }
        fprintf(flog, "\n");
        for (size_t i = 0; i < src->size + 2; i++){
            if (i < src->pointer) {
                fprintf(flog, "* [%d]\n", src->src[i + 2]);
            }
            else {
                fprintf(flog, "  [NONE] \n");
            }
        }
        for (size_t i = 0; i < Cansize; i++){
                fprintf(flog, "[%c]", *(((char*)(src->src + src->size)) + i + Cansize));
        }
        fprintf(flog, "\n");
    }
    fprintf(flog,"\n--------------------------------------------------------------------------------\n");
    return StackCheck(src);
}

size_t Hash(void* st, void* end) {

    assert((char *) end > (char *) st);

    unsigned short A = 1;
    unsigned short B = 0;

    for (size_t i = 0; i < (size_t) ((char*) end - (char *) st); i++) {
        if (Mask & (1 << i)){
            A += *(((unsigned char *) st) + i);
            B += A;
        }
    }
    return B * 65536 + A;
}

#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wreturn-type"
const char *Definition (StackError code ){
#define DEF_ERR(elem) case(elem): return #elem;
    switch (code) {
        DEF_ERR(OK)
        DEF_ERR(EMPTY_STACK)
        DEF_ERR(EMPTY_SOURCE)
        DEF_ERR(STACK_OVERFLOW)
        DEF_ERR(LAZHA)
        DEF_ERR(POPALSYA_NA_HASHE)
    }
}
#pragma GCC diagnostic error "-Wswitch-default"
#pragma GCC diagnostic error "-Wreturn-type"
