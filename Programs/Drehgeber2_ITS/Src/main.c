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
  initITSboard(); // Initialisierung des ITS Boards

  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  TP_Init(false);               // Initialisierung des LCD Boards mit Touch
  initTimer();                  // Timer initialisieren

  double startSchritte;
  double aktuellerWinkel;
  double letzterWinkel = 0.0;
  double geschwindigkeit;
  int letzterPhase = 0;
  uint32_t startZeit = getTimeStamp();

  // Test in Endlosschleife
  while (1) {
    eingabeVerarbeitung();
    HAL_Delay(100);
    bool s6 = readGPIOPIN();
    // wenn taste s6 gedrückt ist, geh rein und setzte alle Variablen zurück
    if (s6 == true) {
      //	fehlerZuruecksetzen();
      lcdPrintS("2"); // es wurde zurückgesetzt;
    }
    if (gibFehler() == false && s6 == true) {
      uint32_t endZeit = getTimeStamp();
      uint32_t deltaZeit = endZeit - startZeit;

      // Wenn die Zeitdifferenz zwischen 250 ms und 500 ms liegt, berechne die
      // Geschwindigkeit und den Drehwinkel
      if (deltaZeit >= 250) {
        startSchritte = gibSchrittzahl();
        int aktuellerPahse = gibPhase();
        if (aktuellerPahse != letzterPhase) {
          aktuellerWinkel = berechneWinkel(startSchritte);
          geschwindigkeit = berechneGeschwindigkeit(
              letzterWinkel, aktuellerWinkel, startZeit, endZeit);
          letzterWinkel = aktuellerWinkel;
          letzterPhase = aktuellerPahse;
          lcdPrintS("es geht"); // dieser if geht
        }
        startZeit = endZeit;
        updateDisplay(aktuellerWinkel, geschwindigkeit);
      }
      lcdPrintS("0"); // Es gab kein Fehler
    } else {
      lcdPrintS("1"); // Es gab ein Fehler bei den Phasen
    }
  }
}

// EOFit.h"
#include "LC
