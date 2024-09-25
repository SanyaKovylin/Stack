#include <stdio.h>
#include "stack.h"

int main(void){
    Stack st = {};
    STACK_ASSERT(st);
    StackCtor(&st, 8);
    StackPush(&st, OK);
    int e = 12;
    DUMP(st);
    StackPop(&st, &e);
    printf("%d",e);
    return 0;
}
