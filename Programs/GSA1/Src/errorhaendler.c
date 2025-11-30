/**
  * @file errorhaendler.c
  * @author MJ
  * @date Oct 2025
  */

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