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

#define maxStackSize 10  

int stackSize = 0;
int index0;
int index1;

bool inEmpty() return stackSize == 0;

int peek() {
    if(isEmpty()) {
        lcdPrintlnS("stack is empty!\n");
    }
    else if (stackSize == 1) {
        return index0;
    }
    else if (stackSize == maxStackSize) {
        return index1;
    }
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
    else {
        lcdPrintlnS("stack Overflow!\n");
    }
}

int pop() {
    if (isEmpty) {
        lcdPrintlnS("stack Underflow!\n");
    }
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

