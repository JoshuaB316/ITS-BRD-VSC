/**
  * @file calculate.c
  * @author MJ
  * @date Oct 2025
  */

#include "calculate.h"
#include "stack.h"
#include <limits.h>
#include <stdio.h>

void +() {
    int firstNum = pop();
    int secondNum = pop();

    if(firstNum + secondNum > INT_MAX) printf("Integer Overflow!\n");
    else if(firstNum + secondNum < INT_MIN) printf("Integer Underflow!\n");
    else {
        int result = firstNum + secondNum;
        push(result);
    }
}

void -() {
    int firstNum = pop();
    int secondNum = pop();
    if(secondNum - secfirstNumondNum > INT_MAX) printf("Integer Overflow!\n");
    else if(secondNum - firstNum < INT_MIN) printf("Integer Underflow!\n");
    else  {
        int result = secondNum - firstNum;
        push(result);
    }
}

void *() {
    int firstNum = pop();
    int secondNum = pop();
    if(firstNum * secondNum > INT_MAX) printf("Integer Overflow!\n");
    else if(firstNum * secondNum < INT_MIN) printf("Integer Underflow!\n");
    else  {
        int result = firstNum * secondNum;
        push(result);
    }
}

void /() {
    int firstNum = pop();
    int secondNum = pop();
    if (firstNum != 0) {
        int result = secondNum / firstNum;
        push(result);
    }
   else {
        printf("cannot divide by 0\n");
        push(secondNum);
        push(firstNum);
    }
}