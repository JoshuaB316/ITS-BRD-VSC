/**
  * @file errorhaendler.c
  * @author MJ
  * @date Oct 2025
  */

#include "errorhaendler.h"

void displayError(int errNum){
    switch (errNum){
        case StackOverflow:
            printStdout("Stack Overflow!\n");
            break;
        case StackUnderflow:
            printStdout("Stack Underflow!\n");
            break;
        case IntOverflow:
            printStdout("Integer Overflow!\n");
            break;
        case IntUnderflow:
            printStdout("Integer Underflow!\n");
            break;
        case DivideByZero:
            printStdout("Cannot divide by zero!\n");
            break;
    }
}