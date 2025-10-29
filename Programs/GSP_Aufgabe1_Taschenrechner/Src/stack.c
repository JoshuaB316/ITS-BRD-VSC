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

#define maxStackSize 10  // auf 10 stellen

int stackSize = 0;
int stackCounter = 0;
int stack[10];

bool isEmpty() return stackSize == 0;

int peek(int *index) {
    
    if(index < stackSize){
        index = stack[index]
        return 0;
    }
    else {
        return -1;
    }
}

int push(int value) {
    
    if(stackCounter <= 9){
        stack[stackCounter] = value
        stackCounter++;
        stackSize++;
        return 0;
    }
    else {
        return -1;
    }
}

int pop(int *result) {
    
    if(stackCounter >= 0 || stackSize > 0){
        result = stack[stackCounter - 1]
        stackCounter--;
        stackSize--;
        return 0;
    }
    else {
        return -1;
    }
}
   
int getStackSize() {
    return stackSize;
}

void clearStack() {
    stackSize = 0;
}

