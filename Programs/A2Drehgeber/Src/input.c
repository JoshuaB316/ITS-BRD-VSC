/**
 * @file    input.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date    Mai 2026
 */

#include "input.h"
#include "outputLEDs.h"
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

// Definitionen für die Pin-Masken
#define IDR_MASK_PIN_0 (0x01U << (0))
#define IDR_MASK_PIN_1 (0x01U << (1))
#define ERROR -1

// Globale Variablen für den Zustand des Drehgebers
int currentPhase = 0; // 0 = a, 1 = b, 2 = c, 3 = d
int lastPhase = 0;
int direction = 0; // 1 = vorwärts, -1 = rückwärts, 0 = kein Phasenwechsel
uint32_t stepCounter = 0; // Anzahl der Phasenwechsel
bool errorOccurred = false;

bool readPinA() {
  if (IDR_MASK_PIN_0 == (GPIOF->IDR & IDR_MASK_PIN_0)) {
    return true;
  } else {
    return false;
  }
}

bool readPinB() {
  if (IDR_MASK_PIN_1 == (GPIOF->IDR & IDR_MASK_PIN_1)) {
    return true;
  } else {
    return false;
  }
}

int determinePhase(bool A, bool B) {
  if (!A && !B)
    return 0; // Phase a
  if (A && !B)
    return 1; // Phase b
  if (A && B)
    return 2; // Phase c
  if (!A && B)
    return 3;   // Phase d

  // Fehler
  return ERROR; 
}

void processInput() {
  bool A = readPinA();
  bool B = readPinB();

  lastPhase = currentPhase;
  currentPhase = determinePhase(A, B);

  // Wenn Phase ungültig ist, errorOccurred = true
  if (currentPhase == ERROR) {
    errorOccurred = true;
  }
  // Wnn keine Änderung dann aus der Funktion raus
  if (lastPhase == currentPhase) {
    return;
  }

  // Phasenübergänge auswerten

  // Vorwärtsbewegung
  if (lastPhase == 0 && currentPhase == 1) {
    // a,b
    direction = 1;
    stepCounter++;
  } else if (lastPhase == 1 && currentPhase == 2) {
    // b,c
    direction = 1;
    stepCounter++;
  } else if (lastPhase == 2 && currentPhase == 3) {
    // c,d
    direction = 1;
    stepCounter++;
  } else if (lastPhase == 3 && currentPhase == 0) {
    // d,a
    direction = 1;
    stepCounter++;
  }

  // Rückwärtsbewegung
  else if (lastPhase == 1 && currentPhase == 0) {
    // b,a
    direction = -1;
    stepCounter--;
  } else if (lastPhase == 2 && currentPhase == 1) {
    // c,b
    direction = -1;
    stepCounter--;
  } else if (lastPhase == 3 && currentPhase == 2) {
    // d,c
    direction = -1;
    stepCounter--;
  } else if (lastPhase == 0 && currentPhase == 3) {
    // a,d
    direction = -1;
    stepCounter--;
  } else {
    // Ungültiger Übergang = Error
    errorOccurred = true;
    setErrorLED();
    return;
  }

  toggleLEDs(stepCounter, direction); // Ausgabe der Schrittzahl auf die LEDs
}