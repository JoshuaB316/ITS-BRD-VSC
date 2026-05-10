/**
 * @file umwandeln.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date Mai 2026
 */

#include "umwandeln.h" 
#include "display.h"
#include <stdbool.h> 
#include <stddef.h>  // Für NULL

static char str[13];



int intToString(int num) {
  int i = 0;
  bool negative = false;

  // 1. Sonderfall Null
  if (num == 0) {
    str[i++] = '0'; // Konvertiere die Ziffer
    str[i] = '\0';  // String-Ende
    reverseString(str, i);
    return 0;
  }

  // Sonderfall negative Zahlen
  if (num < 0) {
    negative = true;
    num = num * (-1); // Arbeite mit dem positiven Wert
  }
  // 2. Konvertiere jede Ziffer in den String
  while (num != 0) {
    int digit = num % 10;
    str[i++] = digit + '0';
    num = num / 10; // Entfernt die letzte Ziffer
  }

  // Füge das Minuszeichen hinzu, falls nötig
  if (negative) {
    str[i++] = '-';
  }

  // String-Ende (Null-Terminator)
  str[i] = '\0';

  // String umkehren, da Ziffern in umgekehrter Reihenfolge gespeichert wurden
  reverseString(str, i);
  return i;
}


void reverseString(char str[], int length) {
  if (str == NULL || length <= 0)
    return;

  char tmp[length + 1]; // Nutze die gleiche Größe wie str
  int s = 0;

  for (int t = length - 1; t >= 0; t--) {
    tmp[s++] = str[t];
  }
  tmp[s] = '\0';

  printStdout(tmp);
}
