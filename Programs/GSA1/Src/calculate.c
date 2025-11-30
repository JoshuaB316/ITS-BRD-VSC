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
#include "display.h"
#include "errorhaendler.h"

int safe_add(int a, int b, int *result) {
    if ((b > 0) && (a > INT_MAX - b)) {
        return IntOverflow; // Overflow
    } else if ((b < 0) && (a < INT_MIN - b)) {
        return IntUnderflow; // Underflow
    } else {
        *result = a + b;
        return 0; // is OK
    }
}

void add() {
    int result1 = 0;
    int err1 = pop(&result1);

    int result2 = 0;
    int err2 = pop(&result2);

    int result;
    if(err1 == 0 && err2 == 0){
        if (safe_add(result1, result2, &result) == IntOverflow){
            displayError(IntOverflow);
            push(result2);
            push(result1);
        }else if(safe_add(result1, result2, &result) == IntUnderflow){
            displayError(IntUnderflow);
            push(result2);
            push(result1);
        } else {
            push(result);
        }
    } else {
       displayError(StackUnderflow);
    }
}

int safe_substract(int a, int b, int *result) {
    if ((b < 0) && (a > INT_MAX + b)) {
        return IntOverflow; // Overflow
    } else if ((b > 0) && (a < INT_MIN + b)) {
        return IntUnderflow; // Underflow
    } else {
        *result = b - a;
        return 0; // is OK
    }
}

extern void subtract() {
    int result1 = 0;
    int err1 = pop(&result1);

    int result2 = 0;
    int err2 = pop(&result2);

    int result;
    if(err1 == 0 && err2 == 0){
        if (safe_substract(result1, result2, &result) == IntOverflow){
            display(IntOverflow)
            push(result2);
            push(result1);
        } else if(safe_substract(result1, result2, &result) == IntUnderflow) {
            display(IntUnderflow)
            push(result2);
            push(result1);
        } else {
            push(result);
        }
    } else {
        displayError(StackUnderflow);
    }
}

int safe_multiply(int a, int b, int *result) {
    if (((a > 0) && (b > 0) && (a > INT_MAX / b)) ||
       ((a < 0) && (b < 0) && (a < INT_MAX / b))) {
        return IntOverflow; // Overflow
    } else if (((a > 0) && (b < 0) && (b < INT_MIN / a)) ||
               ((a < 0) && (b > 0) && (a < INT_MIN / b))) {
        return IntUnderflow; // Underflow
    } else {
        *result = a * b;
        return 0; // is OK
    }
}

extern void multiply() {
    int result1 = 0;
    int err1 = pop(&result1);

    int result2 = 0;
    int err2 = pop(&result2);

    int result;
    if(err1 == 0 && err2 == 0){
        if (safe_multiply(result1, result2, &result) == IntOverflow){
            displayError(IntOverflow);
            push(result2);
            push(result1);
        } else if(safe_multiply(result1, result2, &result) == IntUnderflow) {
            displayError(IntUnderflow);
            push(result2);
            push(result1);
        } else {
            push(result);
        }
    } else {
       displayError(StackUnderflow);
    }
}

int safe_divide(int a, int b, int *result) {
    if (b == 0) {
        return DivideByZero; // Division by zero
    } else if ((a == INT_MIN) && (b == -1)) {
        return IntOverflow; // Overflow
    } else {
        *result = b / a;
        return 0; // is OK
    }
}

extern void divide() {
    int result1 = 0;
    int err1 = pop(&result1);

    int result2 = 0;
    int err2 = pop(&result2);

    int result;
    if(err1 == 0 && err2 == 0){
        if (safe_divide(result1, result2, &result) == IntOverflow){
            displayError(IntOverflow);
            push(result2);
            push(result1);
        } else if(safe_divide(result1, result2, &result) == DivideByZero) {
            displayError(DivideByZero);
        } else {
            push(result);
        }
    } else {
        displayError(StackUnderflow);
    }
}