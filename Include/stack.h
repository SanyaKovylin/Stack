#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <ctype.h>

#include "colors.h"

typedef int type;

struct DebugInfo {
    const char *filename;
    size_t line;
    const char *name;
};

struct Stack {
    type* src;
    size_t pointer;
    size_t size;
    struct DebugInfo info;
};



enum StackError{
    OK                = 0,
    EMPTY_STACK       = 1,
    EMPTY_SOURCE      = 2,
    STACK_OVERFLOW    = 3,
    LAZHA             = 4,
    POPALSYA_NA_HASHE = 5,
};

const int DefaultSize = 8;

StackError StackCtor   (Stack *src, size_t length);
StackError StackPush   (Stack *src, type elem);
StackError StackPop    (Stack *src, type *elem);
StackError StackDump   (Stack *src, const char *file, const int line, const char *errname);
StackError StackCheck  (Stack *src );
const char *Definition (StackError code );
StackError Resize(Stack *src, size_t size, size_t lastsize);
StackError StackDtor(Stack *src);

#define STACK_ASSERT(st) \
    if(StackError c = StackCheck (&st)) \
    { \
        ChangeColourTo(Red);\
        fprintf(stderr, "%s\n",Definition(c));\
        fprintf(stderr ,"%s:%d\n" ,__FILE__, __LINE__);\
        ChangeColourTo(Default);\
        StackDump (&st, __FILE__, __LINE__, Definition(c));\
    }

#define DUMP(st) StackDump (&st, __FILE__, __LINE__, "SimpleDump");

#endif //STACK_H_INCLUDED
