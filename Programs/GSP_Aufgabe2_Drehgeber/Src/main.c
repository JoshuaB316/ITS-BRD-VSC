/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#inlcude "encoder.h"


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	double winkel = 0;
	double winkelges = 0;
	int kanalA;
	int kanalB;


	// Test in Endlosschleife
	while(1) {
		//Datenerfassung
			//Auslesen der Kanäle A und B
			//wurde S6 gedrückt 
			//brauchen lastPhase und currentPhase als variable

		//Datenverarbeitung
			//Auswertung von Kanal A und B + phasenzuordnung
			//letzen phasenwechsel mit neuer phase vergleichen - potenziell fehler
				//a zu b +0,3
				//b zu a -0,3
				//a zu a /
				//a zu c /


		//Steuerung
			//LED für schritte
			//LED für laufrichtung
			//LED für fehler

			//Display
				//Drehwinkel
				//Drehgeschwindigkeit in Grad pro sekunde (timer modul)
	}
}

// EOF
