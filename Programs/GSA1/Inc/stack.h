/**
  * @file stack.h
  * @author MJ test
  * @date Oct 2025
  */

#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#define maxStackSize 10  // auf 10 stellen

extern int stackSize;

/*
 ****************************************************************************************
 *  @brief      This function checks if the Stack is empty
 *
 *  @return     bool 
 ****************************************************************************************/
bool isEmpty();

/*
 ****************************************************************************************
 *  @brief      This function returns the latest value of the Stack
 *
 *  @return     int 
 ****************************************************************************************/
int peek(int index, int *result);

/*
 ****************************************************************************************
 *  @brief      This function adds a value to the Stack
 *
 *  @param      value   value to be added
 *
 *  @return     void 
 ****************************************************************************************/
int push(int value);

/*
 ****************************************************************************************
 *  @brief      This function removes the latest value of the Stack
 *
 *  @return     int 
 ****************************************************************************************/
int pop(int *result);

/*
 ****************************************************************************************
 *  @brief      This function returns the current size of the Stack
 *
 *  @return     int 
 ****************************************************************************************/
int getStackSize();

/*
 ****************************************************************************************
 *  @brief      This function clears the Stack
 *
 *  @return     void 
 ****************************************************************************************/
void clearStack();


#endif
