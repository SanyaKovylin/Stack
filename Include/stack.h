#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include "colors.h"

typedef int type;

struct Stack {
    type* src;
    size_t pointer;
    size_t size;
    struct DebugInfo *info;
};

struct DebugInfo {
    const char *filename;
    int line;
    const char *name;
};

enum StackError{
    OK             = 0,
    EMPTY_STACK    = 1,
    EMPTY_SOURCE   = 2,
    STACK_OVERFLOW = 3,
};


StackError StackCtor   (Stack *src, size_t length);
StackError StackPush   (Stack *src, type elem);
StackError StackPop    (Stack *src, type *elem);
StackError StackDump   (Stack *src, const char *file, const int line);
StackError StackCheck  (Stack *src );
const char *Definition (StackError code );

#define STACK_ASSERT(st) if(StackError c = StackCheck (&st)){ \
    ChangeColourTo(Red);\
    fprintf(stderr, "%s\n",Definition(c));\
    fprintf(stderr ,"%s:%d\n" ,__FILE__, __LINE__);\
    ChangeColourTo(Default);\
    StackDump (&st, __FILE__, __LINE__);\
    }

#define DUMP(st) StackDump (&st, __FILE__, __LINE__);

#endif //STACK_H_INCLUDED
