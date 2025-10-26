/**
  * @file stack.c
  * @author MJ
  * @date Oct 2025
  */

#include "stack.h"
#define maxSize 2 

int stackSize = 0;
int index0;
int index1;

bool isEmpty() return stackSize == 0;

void push(int value){
    if (isEmpty) {
        index0 = value;
        stackSize++;
    }
    else if (stackSize == 1){
        index1 = value;
        stackSize++;
    } 
    else printf("stack Overflow!\n");
}

int pop(){
    if (isEmpty) printf("stack Underflow!\n");
    else if (stacksize == 1) {
        stackSize--;
        return index0;
    }
    else if (stackSize == maxSize){
        stackSize--;
        return index1;
    }
}

int peek(){
    if (isEmpty) printf("stack is empty!\n");
    else if (stackSize == 1) return index0;
    else if (stackSize == maxSize) return index1;
}

int getStackSize(){
    return stackSize;
}

void clearStack(){
    stackSize = 0;
}