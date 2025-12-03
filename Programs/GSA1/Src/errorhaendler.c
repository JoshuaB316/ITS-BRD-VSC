/**
  * @file errorhaendler.c
  * @author MJ
  * @date Oct 2025
  */

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "calculate.h"
#include "operations.h"
#include "toString.h"
#include "token.h"
#include "scanner.h"
#include "stack.h"
#include "display.h"
#include <stdio.h>
#include "errorhaendler.h"

void displayError(int errNum){
    switch (errNum){
        case StackOverflow:
            setErrMode();
            printStdout("Stack Overflow!\n");
            break;
        case StackUnderflow:
            setErrMode();
            printStdout("Stack Underflow!\n");
            break;
        case IntOverflow:
            setErrMode();
            printStdout("Integer Overflow!\n");
            break;
        case IntUnderflow:
            setErrMode();
            printStdout("Integer Underflow!\n");
            break;
        case DivideByZero:
            setErrMode();
            printStdout("Cannot divide by zero!\n");
            break;
        case UnexpectedToken:
            setErrMode();
            printStdout("Unexpected Token!\n");
            break;
        case UnknownToken:
            setErrMode();
            printStdout("Unknown Token!\n");
            break;
        case EmptyStack:
            setErrMode();
            printStdout("Stack is Empty!\n");
            break;
        case NotEnoughElements:
            setErrMode();
            printStdout("Not enough Elements!\n");
            break;
    }
}