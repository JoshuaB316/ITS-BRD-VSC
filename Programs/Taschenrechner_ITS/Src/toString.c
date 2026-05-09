/**
  * @file toString.c
  * @author MJ
  * @date Oct 2025
  */


#include "toString.h"
#include <stdio.h>

void intToString(int value, char *str){

    int i = 0;
    int isNegative = 0;
    unsigned int uValue = 0;

    if(value < 0) {
        isNegative = 1;
        uValue = (unsigned int)(-value);
    }
    else{
        uValue = (unsigned int)value;
    }

    do{
        int digit = uValue % 10;
        str[i++] = '0' + digit;
        uValue /= 10;
    }
    while(uValue > 0);

    if(isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for(int j = 0; j < i; j++ , i--) {
        char temp = str[j];
        str[j] = str[i - 1];
        str[i - 1] = temp;
    }
}