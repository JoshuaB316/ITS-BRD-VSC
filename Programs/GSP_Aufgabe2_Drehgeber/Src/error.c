/**
  * @file error.c
  * @author MJ
  * @date Nov 2025
  */

#include "error.h"
#include "stm32f4xx_hal.h"
#include "lcd.h"
#include "encoder.h"
#include "led_control.h"
#include "display.h"


// Variablen für Winkel
	double angle = 0;
	double angleSpeed = 0;
	double lastAngle = 0;
	double newAngle = 0;
	
	// Variablen für Kanalverarbeitung
	bool channelA = 0;
	bool channelB = 0;
	int lastPhase = 0;
	int currentPhase = 0;
	int phaseCounter = 0;

	int direction = -1; 

void reset() {
    // Variablen für Winkel zurücksetzen
    double angle = 0;
    double angleSpeed = 0;
    double lastAngle = 0;
    double newAngle = 0;
	
    // Variablen für Kanalverarbeitung zurücksetzen
    bool channelA = 0;
    bool channelB = 0;
    int lastPhase = 0;
    int currentPhase = 0;
    int phaseCounter = 0;

    // Wert für "direction" zurücksetzen
    int direction = -1; 
    
    // LEDs zurücksetzen
    ledReset();

    // Display zurücksetzen
    display_update();
}
