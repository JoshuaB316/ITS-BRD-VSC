/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
*/

#include "LCD_Touch.h"
#include "additionalFonts.h"
#include "fontsFLASH.h"
#include "inD_GUI.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#include "input.h"
#include "error.h"
#include "calculate.h"
#include "toString.h"
#include "timer.h"
#include "outputLEDs.h"
#include <stdint.h>

int main() {
  // Initialisierungen
  initITSboard();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);
  initTimer();

  // Variablen
  double startSteps;
  double currentAngle;
  double lastAngle = 0.0;
  double angleSpeed;
  uint32_t startingTime = getTimeStamp();

  // Test in Endlosschleife
  while (1) {
    processInput();
    //HAL_Delay(100);

    // Überprüfen on S6 gedrückt wurde und dementsprechend handeln
    bool s6 = readPinS6();
    if (s6 == true) {
      errorReset();
      // Test ###################################
      //lcdPrintS("2"); // es wurde zurückgesetzt;
    }

    if (errorOccurred == false && s6 == true) {
      uint32_t endingTime = getTimeStamp();
      uint32_t deltaTime = endingTime - startingTime;

      // Wenn die Zeitdifferenz zwischen 250 ms und 500 ms liegt -> Geschwindigkeit und den Drehwinkel berechnen
      if (deltaTime >= 250) {
        startSteps = stepCounter;

        if (currentPhase != lastPhase) {
          currentAngle = calculateDegree(startSteps);
          angleSpeed = calculateAnglespeed(lastAngle, currentAngle, startingTime, endingTime);
          lastAngle = currentAngle;
          lastPhase = currentPhase;
          // Test ###################################
          // lcdPrintS("Funktioniert"); // if-Funktioniert
        }

        startingTime = endingTime;
        //updateDisplay(currentAngle, speed);

        // Ausgabe Winkel
        char currentAngleStr[12]; // vllt lieber andere Zahl als 12
        doubleToString(currentAngle, currentAngleStr)
        lcdPrintS(currentAngleStr);

        // Ausgabe Winkelgeschwindigkeit
        char speedStr[12]; // auch hier vllt andere Zahl
        doubleToString(angleSpeed, speedStr)
        lcdPrintS(speedStr);
      }

      // Test ###################################
      //lcdPrintS("0"); // Es gab kein Fehler

    } else {
      // Test ###################################
      //lcdPrintS("1"); // Es gab ein Fehler bei den Phasen
    }
  }
}
