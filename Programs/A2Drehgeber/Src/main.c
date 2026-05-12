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
#include "LCD_GUI.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "init.h"

#include "display.h"
#include "input.h"
#include "myError.h"
#include "calculate.h"
#include "toString.h"
#include "output.h"
#include "timer.h"
#include "outputLEDs.h"
#include <stdint.h>

int main() {
  // Initialisierungen
  initITSboard();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);
  initTimer();

  readInitialInput();

  // Variablen
  double currentAngle = 0.0;
  double lastAngle = 0.0;
  double angleSpeed = 0.0;
  uint32_t startingTime = getTimeStamp();

  lcdGotoXY(1, 2);
  lcdPrintS("Winkel:");

  lcdGotoXY(1, 4);
  lcdPrintS("Geschwindigkeit:");

  // Test in Endlosschleife
  while (1) {
    processInput();

    // Überprüfen on S6 gedrückt wurde und dementsprechend handeln
    bool s6 = readPinS6();
    if (s6) {
      errorReset();
    }

    if (!errorOccurred) {
      uint32_t endingTime = getTimeStamp();
      uint32_t deltaTime = endingTime - startingTime;

      // Wenn die Zeitdifferenz zwischen 250 ms und 500 ms liegt -> Geschwindigkeit und den Drehwinkel berechnen
      if ((deltaTime >= (250 * 1000 * TICKS_PER_US) && currentPhase != lastPhase) ||
        (deltaTime >= (500 * 1000 * TICKS_PER_US))) {

        currentAngle = calculateDegree(stepCounter);
        angleSpeed = calculateAnglespeed(lastAngle, currentAngle, deltaTime);
        lastAngle = currentAngle;

        startingTime = endingTime;

        outputChange(currentAngle, angleSpeed);
      }

      lastPhase = currentPhase;
    }
    else
    {
      setErrorLED();
    }

    setLEDs(stepCounter, direction); // Ausgabe der Schrittzahl auf die LEDs
    outputUpdate();
  }
}
