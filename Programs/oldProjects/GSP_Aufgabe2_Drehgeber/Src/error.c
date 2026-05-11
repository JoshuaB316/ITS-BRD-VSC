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
angle = 0;
angleSpeed = 0;
lastAngle = 0;
newAngle = 0;
	
// Variablen für Kanalverarbeitung
channelA = 0;
hannelB = 0;
lastPhase = 0;
currentPhase = 0;
phaseCounter = 0;

direction = -1; 

void reset() {
    // Variablen für Winkel zurücksetzen
    angle = 0;
    angleSpeed = 0;
    lastAngle = 0;
    newAngle = 0;
	
    // Variablen für Kanalverarbeitung zurücksetzen
    channelA = 0;
    channelB = 0;
    lastPhase = 0;
    currentPhase = 0;
    phaseCounter = 0;

    // Wert für "direction" zurücksetzen
    direction = -1; 
    
    // LEDs zurücksetzen
    ledReset();

    // Display zurücksetzen
    display_update();
}
