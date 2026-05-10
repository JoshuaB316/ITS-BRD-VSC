/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "LCD_Touch.h"
#include "additionalFonts.h"
#include "ausgabeLEDs.h"
#include "fontsFLASH.h"
#include "inD_GUI.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#include "display_update.h"
#include "eingabe.h"
#include "error.h"
#include "rechnen.h"
#include "timer.h"
#include <stdint.h>

int main(void) {
  // Initialisierungen
  initITSboard(); // Initialisierung des ITS Boards
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);
  initTimer();

  // Variablen
  double startSteps;
  double currentAngle;
  double lastAngle = 0.0;
  double speed;
  int letzterPhase = 0;
  uint32_t startingTime = getTimeStamp();

  // Test in Endlosschleife
  while (1) {
    processInput();
    HAL_Delay(100);

    bool s6 = readPinS6();
    // wenn taste s6 gedrückt ist, geh rein und setzte alle Variablen zurück
    if (s6 == true) {
      errorReset();
      lcdPrintS("2"); // es wurde zurückgesetzt;
    }
    if (gibFehler() == false && s6 == true) {
      uint32_t endingTime = getTimeStamp();
      uint32_t deltaTime = endingTime - startingTime;

      // Wenn die Zeitdifferenz zwischen 250 ms und 500 ms liegt, berechne die
      // Geschwindigkeit und den Drehwinkel
      if (deltaTime >= 250) {
        startSteps = gibSchrittzahl();
        //int aktuellerPahse = gibPhase();
        if (currentPhase != letzterPhase) {
          currentAngle = calculateDegree(startSteps);
          speed = calculateSpeed(lastAngle, currentAngle, startingTime, endingTime);
          lastAngle = currentAngle;
          letzterPhase = currentPhase;
          lcdPrintS("es geht"); // dieser if geht
        }
        startingTime = endingTime;
        updateDisplay(currentAngle, speed);
      }
      lcdPrintS("0"); // Es gab kein Fehler
    } else {
      lcdPrintS("1"); // Es gab ein Fehler bei den Phasen
    }
  }
}

#include "LC
