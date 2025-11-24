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

void p() {

    int result;
    int err = peek(getStackSize() - 1, &result);

    if(err == -1){
        printStdout("Error\n");
        return;
    }
    else {
        char str[12]; //max int = 10 + "-" + "\0" = 12
        intToString(result, str);
        lcdPrintlnS(str);
    }
}

void P() {
    if (isEmpty()) {

        printStdout("Stack is Empty!\n");
        return;
    }
    
    int stackSize = getStackSize();

    int result[10]; //max stack size is 10
    char str[12];

    for(int i = 0; i < stackSize; i++) {
        int temp;
        int err = peek(stackSize - 1 - i, &temp);
        if(err == -1) {
            printStdout("Error\n");
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

    if(isEmpty()){
        printStdout("stack is empty cant duplicate!\n");
        return;
    }

    int result;
    int err = peek(getStackSize() - 1, &result);

    if(err == -1){
        printStdout("Error\n");
        return;
    }

    push(result);
}
    

void r() {

    if (getStackSize() < 2) {
        printStdout("Stack doesn't contain two elements!\n");
        return;
    }

    int val1; 
    int val2;

    if (pop(&val1) == -1) {
        printStdout("Error\n");
        return;
    }

    if (pop(&val2) == -1) {
        printStdout("Error\n");
        push(val1);
        return;
    }

    push(val1); 
    push(val2); 
}
