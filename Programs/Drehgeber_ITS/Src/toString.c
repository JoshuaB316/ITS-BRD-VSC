/**
  * @file toString.c
  * @author MJ
  * @date Oct 2025
  */

#include "toString.h"
#include <stdio.h>

#include <math.h>

void doubleToString(double value, char *str) {
    int i = 0;
    int isNegative = 0;
    double absValue = value;
    int precision = 3; // Anzahl der Nachkommastellen

    if (value < 0) {
        isNegative = 1;
        absValue = -value;
    }

    // Ganzzahlteil
    long intPart = (long)absValue;
    // Nachkommateil
    double fracPart = absValue - intPart;

    // Ganzzahlteil umwandeln
    if (intPart == 0) {
        str[i++] = '0';
    } else {
        while (intPart > 0) {
            str[i++] = '0' + (intPart % 10);
            intPart /= 10;
        }
    }

    // Nachkommastellen umwandeln (precision)
    str[i++] = '.';
    for (int k = 0; k < precision; k++) {
        fracPart *= 10;
        int digit = (int)fracPart;
        str[i++] = '0' + digit;
        fracPart -= digit;
    }

    // Vorzeichen hinzufügen, falls negativ
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    int pointIndex = i - 1 - precision;

    // Nur den Teil vom Vorzeichen bis zum Punkt umkehren
    int left = isNegative ? 1 : 0;
    int right = pointIndex - 1; // Stoppt vor dem Punkt

    // String umkehren aber \0 bleibt (Nullterminator) unter bachtung von punkt und minus
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}