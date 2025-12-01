/**
  * @file errorManager.c
  * @author MJ
  * @date Nov 2025
  */

#include "errorManager.h"
#include "stm32f4xx_hal.h"
#include "lcd.h"
#include "encoder.h"
#include "led_control.h"
#include "display.h"
#include <stdbool.h>


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
