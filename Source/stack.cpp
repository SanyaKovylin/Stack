#include <stdio.h>

#include "stack.h"

#define DebugOn



StackError StackCtor (Stack *src, size_t length){
    src->src = (type *) calloc (length, sizeof(type));
    src->size = length;
    src->pointer = 0;
    STACK_ASSERT(*src);
    return OK;
}

StackError StackPush (Stack *src, type elem){
    STACK_ASSERT(*src);
    src->src[src->pointer] = elem;
    src->pointer++;
    STACK_ASSERT(*src);
    return OK;
}
StackError StackPop (Stack *src, type *elem){
    STACK_ASSERT(*src);
    src->pointer--;
    *elem = src->src[src->pointer];
    src->src[src->pointer] = 0;
    STACK_ASSERT(*src);
    return OK;
}

StackError StackCheck (Stack *src) {

    if (src == NULL)                return EMPTY_STACK   ;
    if (src->src == NULL)           return EMPTY_SOURCE  ;
    if (src->pointer >= src->size && src->size != 0)  return STACK_OVERFLOW;
    return OK;
}

StackError StackDump(Stack *src, const char *file, const int line) {
    FILE *flog = fopen("Stack.log", "w");

    fprintf(flog, "Error    %s:%d\n", file, line);
    for (size_t i = 0; i < src->size; i++){
        printf("%d", src->src[i]);
    }
    fclose(flog);
    return OK;
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
    }
}
#pragma GCC diagnostic error "-Wswitch-default"
#pragma GCC diagnostic error "-Wreturn-type"
