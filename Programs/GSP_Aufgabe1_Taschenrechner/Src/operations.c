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

int p() {

    int result = getStackSize();
    int err = peek(*result);

    if(err == -1){
        lcdPrintlnS("Error");
        return 0;
    }
    else {
        return result;
    }
}

int[] P() {

    int stackLength = getStackSize();

    int result[stackLength];

    if(!isEmpty()){
        for(int i= 0; i <= stackLength; i++, stackLength--){
            int temp = stacklength - 1;
            int err = peek(*temp);

            if(err == -1){
                lcdPrintlnS("Error");
                return 0;
            }
            else {
                result[i] = temp;
            }
        }
    }
}

void C() {
    clearStack();
}

void d() {
    int duplicate = peek();

    if(getSize() == 2) {
        clearStack();
        push(duplicate);
        push(duplicate);
    }
    else if(getStackSize() == 1) {
        push(duplicate);
    }
    else {    
        lcdPrintlnS("stack is empty!\n");
    }
}
    

void r() {
    if (getSize() == 2) {
        int n2 = pop();
        int n1 = pop();
        push(n2);
        push(n1);
    } else {
        lcdPrintlnS("not enough elements to swap!\n");
    }
}
