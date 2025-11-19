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


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	double angle = 0;
	double angleSpeed = 0;
	double lastAngle = 0;
	double newAngle = 0;
	int phaseCounter = 0;
	int lastPhase = 0;
	int currentPhase = 0;
	int direction = -1; // -1 bei fehler, 0 rechts, 1
	bool existingError = false;
	bool channelA = 0;
	bool channelB = 0;
	uint32_t timer_start = getTimeStamp();
	uint32_t timer_end;

  // Timer initialisieren

	// Test in Endlosschleife
	while(1) {
		//Datenerfassung
			channelA = givePinA();
			channelB = givePinB();

			//wurde S6 gedrückt ? 
			if(existingError){
				if(MODER_MASK_PIN_6 == (GPIOF -> IDR & MODER_MASK_PIN_6)){
					reset();
				}
			}

		//Datenverarbeitung
			//Auswertung von Kanal A und B + phasenzuordnung
			
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

			angleSpeed = angle / timer_diff();

		//Steuerung
			//LED für schritte
			ledNextStep();

			//LED für laufrichtung
			ledDirection(direction);

			//LED für fehler
			if(existingError){
				ledError();
			}

			//Display
				//Drehwinkel
				timer_end = getTimeStamp();
					// alter Winkel - neuer Winkel / Zeitdifferenz
				//Drehgeschwindigkeit in Grad pro sekunde (timer modul)
				lastAngle = newAngle;
				newAngle = angle;
				timer_start = timer_end;
	}
}

// EOF
