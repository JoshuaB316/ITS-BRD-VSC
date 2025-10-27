/**
  * @file toString.h
  * @author MJ test
  * @date Oct 2025
  */

#include toString.h
#include <stdio.h>

void intToString(int value, char *str) {
    int i = 0;
    int isNegative = 0;

    if(value < 0){
    isNegative = 1;
    value = value * (-1);
    }

    do {    
    int digit = value % 10;
    str[i++] = '0' + digit;
    value /= 10;
    }
    while (value > 0);

    if (isNegative) {
    str[i++] = '-';
    }

    str[i] = '\0';

    for (int j = 0; j < i / 2; j++, i--) {
    char temp = str[j];
    str[j] = str[i - 1];
    str[i - 1] = temp;
    }

}