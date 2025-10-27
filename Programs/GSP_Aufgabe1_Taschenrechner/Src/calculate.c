/**
  * @file calculate.c
  * @author MJ
  * @date Oct 2025
  */

#include "calculate.h"
#include "stack.h"
#include <limits.h>
#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"

extern void add() {
    int firstNum = pop();
    int secondNum = pop();

    if (firstNum + secondNum > INT_MAX) {
        lcdPrintlnS("Integer Overflow!\n");
    }
    else if(firstNum + secondNum < INT_MIN) {
        lcdPrintlnS("Integer Underflow!\n");
    }
    else {
        int result = firstNum + secondNum;
        push(result);
    }
}

void subtract() {
    int firstNum = pop();
    int secondNum = pop();
    if(secondNum - secfirstNumondNum > INT_MAX){
        lcdPrintlnS("Integer Overflow!\n");
    }
    else if(secondNum - firstNum < INT_MIN){
        lcdPrintlnS("Integer Underflow!\n");
    }
    else  {
        int result = secondNum - firstNum;
        push(result);
    }
}

void multiply() {
    int firstNum = pop();
    int secondNum = pop();
    if(firstNum * secondNum > INT_MAX){
        lcdPrintlnS("Integer Overflow!\n");
    }
    else if(firstNum * secondNum < INT_MIN){
        lcdPrintlnS("Integer Underflow!\n");
    }
    else  {
        int result = firstNum * secondNum;
        push(result);
    }
}

void divide() {
    int firstNum = pop();
    int secondNum = pop();
    if (firstNum != 0) {
        int result = secondNum / firstNum;
        push(result);
    }
   else {
        lcdPrintlnS("cannot divide by 0\n");
        push(secondNum);
        push(firstNum);
    }
}