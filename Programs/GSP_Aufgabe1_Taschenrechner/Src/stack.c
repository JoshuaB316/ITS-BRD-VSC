/**
  * @file stack.c
  * @author MJ
  * @date Oct 2025
  */


#include "stack.h"
#include <stdio.h>

#define maxStackSize 2

int stackSize = 0;
int index0;
int index1;

bool inEmpty() return stackSize == 0;

int peek(int index) {
    if(isEmpty()) printf("stack is empty!\n");
    else if (stackSize == 1) return index0;
    else if (stackSize == maxStackSize) return index1;
}

void push(int value) {
    if (isEmpty) {
        index0 = value;
        stackSize++;
    } 
    else if (stackSize == 1) {
        index1 = value;
        stackSize++;
    }
    else printf("stack Overflow!\n");
}

int pop() {
    if (isEmpty) printf("stack Underflow!\n");
    else if (stackSize == 1) {
        stackSize--;
        return index0;
    }
    else if (stackSize == maxStackSize) {
        stackSize--;
        return index1;
    }
}
   
int getStackSize() {
    return stackSize;
}

void clearStack() {
    stackSize = 0;
}

