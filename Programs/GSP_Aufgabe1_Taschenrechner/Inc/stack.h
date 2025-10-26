/**
  * @file stack.h
  * @author MJ
  * @date Oct 2025
  */

#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

bool isEmpty();

void push(int value);

int pop();

int peek();

int getStackSize();

void clearStack();



#endif

