/**
 * @file eingabe.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date Mai 2026
 */

#include "eingabe.h"
#include "ausgabeLEDs.h"
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

// Definitionen für die Pin-Masken
#define IDR_MASK_PIN_0 (0x01U << (0))
#define IDR_MASK_PIN_1 (0x01U << (1))
#define ERROR -1
#define OK 0

// Globale Variablen für den Zustand des Drehgebers
int currentPhase = 0; // 0 = a, 1 = b, 2 = c, 3 = d
int lastPhase = 0;
int direction = 0;            // 1 = vorwärts, -1 = rückwärts, 0 = keine Änderung
uint32_t stepCounter = 0; // Zählt die Phasenwechsel
bool errorOccurred = false; // Wird true, wenn ein ungültiger Übergang erkannt wird

bool readPinA(void) {
  if (IDR_MASK_PIN_0 == (GPIOF->IDR & IDR_MASK_PIN_0)) {
    return true;
  } else {
    return false;
  }
}

bool readPinB(void) {
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
  return ERROR; // Fehler
}

void processInput(void) {
  bool A = readPinA();
  bool B = readPinB();

  lastPhase = currentPhase;
  currentPhase = determinePhase(A, B);

  // Wenn Phase ungültig ist, Fehler setzen
  if (currentPhase == ERROR) {
    errorOccurred = true;
  }
  // Keine Änderung → nichts tun
  if (lastPhase == currentPhase) {
    return; // Beende die Funktion sofort.
  }

  // Phasenübergänge auswerten (nach Tabelle aus der Aufgabe)
  // Vorwärtsbewegung
  if (lastPhase == 0 && currentPhase == 1) {
    // a → b = Vorwärtsbewegung
    direction = 1;
    stepCounter++;
  } else if (lastPhase == 1 && currentPhase == 2) {
    // b → c = Vorwärtsbewegung
    direction = 1;
    stepCounter++;
  } else if (lastPhase == 2 && currentPhase == 3) {
    // c → d = Vorwärtsbewegung
    direction = 1;
    stepCounter++;
  } else if (lastPhase == 3 && currentPhase == 0) {
    direction = 1;
    stepCounter++;
  }

  // Rückwärtsbewegung
  else if (lastPhase == 1 && currentPhase == 0) {
    // b → a = Rückwärtsbewegung
    direction = -1;
    stepCounter--;
  } else if (lastPhase == 2 && currentPhase == 1) {
    // c → b = Rückwärtsbewegung
    direction = -1;
    stepCounter--;
  } else if (lastPhase == 3 && currentPhase == 2) {
    // d → c = Rückwärtsbewegung
    direction = -1;
    stepCounter--;
  } else if (lastPhase == 0 && currentPhase == 3) {
    direction = -1;
    stepCounter--;
  }

  else {
    // Alle anderen Übergänge sind ungültig
    errorOccurred = true;
    setErrorLED();
    // led 21 muss ausgehen
    return;
  }

  toggleLEDs(stepCounter, direction); // Ausgabe der Schrittzahl auf die LEDs
}

//int gibPhase() { return aktuellePhase; }
//int gibSchrittzahl(void) { return schrittZaehler; }

//bool gibFehler(void) { return fehler; }
