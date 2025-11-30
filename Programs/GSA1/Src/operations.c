/**
  * @file operations.c
  * @author MJ
  * @date Oct 2025
  */

#include "operations.h"
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
#include "toString.h"
#include "display.h"
#include "errorhaendler.h"
#include "stack.h"

void p() {
    if (isEmpty()) {
        displayError(EmptyStack);
        return;
    }

    int result;
    int err = peek(getStackSize() - 1, &result);

    if(err == StackUnderflow){
        displayError(StackUnderflow);
        return;
    }
    else {
        char str[12]; //max int = 10 + "-" + "\0" = 12
        intToString(result, str);
        printStdout(str);
    }
}

void P() {
    if (isEmpty()) {
        displayError(EmptyStack);
        return;
    }
    
    int stackSize = getStackSize();

    int result[maxStackSize]; //max stack size is 10
    char str[12];

    for(int i = 0; i < stackSize; i++) {
        int temp;
        int err = peek(stackSize - 1 - i, &temp);
        if(err == StackUnderflow) {
            displayError(StackUnderflow);
            return;
        }
        result[i] = temp;
    }
    
    for(int i = 0; i < stackSize; i++) {
        intToString(result[i], str);
        printStdout(str);
    }
}

void C() {
    clearStack();
}

void d() {
    if (isEmpty()) {
        displayError(EmptyStack);
        return;
    }

    int result;
    int err = peek(getStackSize() - 1, &result);

    if(err == StackUnderflow){
        displayError(StackUnderflow);
        return;
    }

    if(getStackSize() + 1 <= maxStackSize){
        push(result);
    } else {
        displayError(StackOverflow);
    }
    
}
    

void r() {

    if (getStackSize() < 2) {
        displayError(NotEnoughElements);
        return;
    }

    int val1; 
    int val2;

    if (pop(&val1) == StackUnderflow) {
        displayError(StackUnderflow);
        return;
    }

    if (pop(&val2) == StackUnderflow) {
        displayError(StackUnderflow);
        push(val1);
        return;
    }

    push(val1); 
    push(val2); 
}
