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

int p() {
    if (stackSize == 0) {
        return EmptyStack;
    }

    int result;
    int err = peek(stackSize - 1, &result);

    if(err == StackUnderflow){
        return StackUnderflow;
    }
    else {
        char str[12]; //max int = 10 + "-" + "\0" = 12
        intToString(result, str);
        printStdout(str);
    }
    return 0;
}

int P() {
    if (stackSize == 0) {
        return EmptyStack;
    }

    int result[maxStackSize]; //max stack size is 10
    char str[12];

    for(int i = 0; i < stackSize; i++) {
        int temp;
        int err = peek(stackSize - 1 - i, &temp);
        if(err == StackUnderflow) {
            return StackUnderflow;
        }
        result[i] = temp;
    }
    
    for(int i = 0; i < stackSize; i++) {
        intToString(result[i], str);
        printStdout(str);
        printStdout("\n");
    }
    return 0;
}

void C() {
    stackSize == 0;
}

int d() {
    if (stackSize == 0) {
       return EmptyStack;
    }

    int result;
    int err = peek(stackSize - 1, &result);

    if(err == StackUnderflow){
        return StackUnderflow;
    }

    if(stackSize + 1 <= maxStackSize){
        push(result);
    } else {
        return StackOverflow;
    }
    return 0;
}
    

int r() {

    if (stackSize < 2) {
        return NotEnoughElements;
    }

    int val1; 
    int val2;

    if (pop(&val1) == StackUnderflow) {
        return StackUnderflow;
    }

    if (pop(&val2) == StackUnderflow) {
        //displayError(StackUnderflow);
        push(val1);
        return StackUnderflow;
    }

    push(val1); 
    push(val2); 
    
    return 0;
}
