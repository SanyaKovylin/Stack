#include <stdio.h>
#include "stack.h"

int main(void){
    Stack st = {};
    STACK_ASSERT(st);
    StackCtor(&st, 8);
    for (int i = 1; i < 116; i++)
        StackPush(&st, i);
    int e = 12;
    DUMP(st);
    for  (int i = 0; i < 100; i++){
        StackPop(&st, &e);
        printf("%d\n",e);
    }
    printf("%d",e);
    return 0;
}
