/**
  * @file operations.c
  * @author MJ
  * @date Oct 2025
  */

#include "operations.h"
#include "stack.h"

int p() {
    return peek();
}

int[] P() {
    if(getSize() == 2) {
        int n2 = pop();
        int n1 = pop();
        int[] result = {n1, n2};
        push(n1);
        push(n2);
        return result;
    }
    else if(getStackSize() == 1) {
        return peek();
    }
    else {    
        return printf("stack is empty!\n");
    }
}

void C() clearStack();

void d() {
    int duplicate = peek();

    if(getSize() == 2) {
        clearStack();
        push(duplicate);
        push(duplicate);
    }
    else if(getStackSize() == 1) {
        push(duplicate);
    }
    else {    
        return printf("stack is empty!\n");
    }
}
    

void r() {
   if(getSize() == 2) {
    int n2 = pop();
    int n1 = pop();
    push(n2);
    push(n1);
   }
   else printf("not enough elements to swap!\n");
}
