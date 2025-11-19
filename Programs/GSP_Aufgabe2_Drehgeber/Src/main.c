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
#include "encoder.h"
#include "led_control.h"
#include "display.h"
#include <stdbool.h>
#include <stdio.h>
#include "timer.h"

#define MODER_MASK_PIN_6   (0x03U << (2*6)) // Pin 6 
#define GPIOF_PORT GPIOF	


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  	// Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	// Fehlererkennung
	bool existingError = false;
	
	// Timer initialisieren
	uint32_t timer_start = getTimeStamp();
	uint32_t timer_end;

	// Test in Endlosschleife
	while(1) {
		// Datenerfassung
			// Gibt es Fehler und wurde S6 gedrückt?
			if(existingError){
				if(MODER_MASK_PIN_6 == (GPIOF -> IDR & MODER_MASK_PIN_6)){
					reset();
				}
			}

			// Kanäle einlesen
			channelA = givePinA();
			channelB = givePinB();

		// Datenverarbeitung
			// Auswertung von Kanal A und B um Phase und Richtung zu bestimmen
			currentPhase = getPhase(channelA, channelB);
			direction = getDirection(lastPhase, currentPhase);
			lastPhase = currentPhase;

			if(direction == -1){
				existingError = true;
				ledError();
				display_error()
			} else if(direction == 0){
				angle += 0,3;
				phaseCounter++;
			} else if(direction == 1){
				angle -= 0,3;
				phaseCounter++;
			}

			// Berechnung der Winkelgeschwindigkeit
			timer_end = getTimeStamp();
			angleSpeed = (lastAngle - newAngle) / (timer_end - timer_start);

		// Steuerung
			// bei Fehler keine Steuerung
			if(!existingError){
				ledNextStep();
				ledDirection(direction);
				// DisplayAusgabe
			} else {
				ledError();
			}
			
			// Update der Variablen
			lastAngle = newAngle;
			newAngle = angle;
			timer_start = timer_end;
	}
}

// EOF
