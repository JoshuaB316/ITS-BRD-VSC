/**
  * @file stack.c
  * @author MJ
  * @date Oct 2025
  */


#include "stack.h"
#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "display.h"
#include "errorhaendler.h"



int stackSize = 0;
int stack[10];

bool isEmpty() {
    return stackSize == 0;
}

int peek(int index, int *result) {
    
    if(index >= 0 && index < stackSize){
        *result = stack[index];
        return 0;
    }
    else {
        return StackUnderflow;
    }
}

int push(int value) {

    if(stackSize <= 9){
        stack[stackSize] = value;
        stackSize++;
        return 0;
    }
    else {
        return StackOverflow;
    }
}

int pop(int *result) {
    
    if(stackSize > 0){
        *result = stack[stackSize - 1];
        stackSize--;
        return 0;
    }
    else {
        return StackUnderflow;
    }
}
   
int getStackSize() {
    return stackSize;
}

void clearStack() {
    stackSize = 0; //verlieren von referenzen
}

