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

int safe_add(int a, int b, int *result) {
    if ((b > 0) && (a > INT_MAX -b)) {
        return 1; // Overflow
    } else if ((b < 0) && (a < INT_MIN - b)) {
        return 1; // Underflow
    } else {
        *result = a + b;
        return 0; // is OK
    }
}

extern void add() {
    int firstNum = pop();
    int secondNum = pop();
    int result;

    if (!safe_add(firstNum, secondNum, &result)){
        lcdPrintlnS("Integer Overflow / Underflow!\n");
    } else {
        push(result);
    }
}

int safe:substract(int a, int b, int *result) {
    if ((b < 0) && (a > INT_MAX + b)) {
        return 1; // Overflow
    } else if ((b > 0) && (a < INT_MIN + b)) {
        return 1; // Underflow
    } else {
        *result = a - b;
        return 0; // is OK
    }
}

extern void subtract() {
    int firstNum = pop();
    int secondNum = pop();
    int result;

    if (!safe_substract(secondNum, firstNum, &result)){
        lcdPrintlnS("Integer Overflow / Underflow!\n");
    } else {
        push(result);
    }
}

int safe_multiply(int a, int b, int *result) {
    if (((a > 0) && (b > 0) && (a > INT_MAX / b)) ||
       ((a < 0) && (b < 0) && (a < INT_MAX / b))) {
        return 1; // Overflow
    } else if (((a > 0) && (b < 0) && (b < INT_MIN / a)) ||
               ((a < 0) && (b > 0) && (a < INT_MIN / b))) {
        return 1; // Underflow
    } else {
        *result = a * b;
        return 0; // is OK
    }
}

extern void multiply() {
    int firstNum = pop();
    int secondNum = pop();
    int result;

    if (!safe_multiply(firstNum, secondNum, &result)){
        lcdPrintlnS("Integer Overflow / Underflow!\n");
    } else {
        push(result);
    }
}

int safe_divide(int a, int b, int *result) {
    if (b == 0) {
        return 1; // Division by zero
    } else if ((a == INT_MIN) && (b == -1)) {
        return 1; // Overflow
    } else {
        *result = a / b;
        return 0; // is OK
    }
}

extern void divide() {
    int firstNum = pop();
    int secondNum = pop();
    int result;

    if (!safe_divide(secondNum, firstNum, &result)){
        lcdPrintlnS("Error: Division by zero or Integer Overflow!\n");
    } else {
        push(result);
    }
}