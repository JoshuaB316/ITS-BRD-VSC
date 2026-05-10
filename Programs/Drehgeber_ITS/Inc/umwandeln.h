/**
 * @file umwandeln.h
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date Mai 2026
 */

#ifndef UMWANDELN_H
#define UMWANDELN_H

#include <stdbool.h> // Für bool, true, false


/**
 * @brief Wandelt eine Ganzzahl in einen String um.
 * @param num Die Zahl, die umgewandelt werden soll.
 */
int intToString(int num);


/**
 * @brief Gibt einen String rückwärts aus (für die korrekte Display-Ausgabe).
 * @param str Zeiger auf den String, der ausgegeben werden soll.
 * @param length Länge des Strings
 */
void reverseString(char str[], int length);


#endif