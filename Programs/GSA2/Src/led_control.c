/**
  * @file led_control.c
  * @author MJ
  * @date Nov 2025
  */

#include "led_control.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "errorManager.h"

#define LED_PORT GPIOD
#define nextStepCounter 8


void ledNextStep() {
    // alle LEDs aus
    GPIOD->BSRR = 0xFFFF0000; 

    // schaltet nächste LED an
    GPIOD->BSRR = (0x01 << (nextStepCounter)); 
    nextStepCounter++;

    // zurücksetzen auf erste LED wenn die Letzte erreicht wurde
    if (nextStepCounter > 15) {
        nextStepCounter = 8; 
    }
}


void ledReset() {
    // alle LEDs aus
    GPIOD->BSRR = 0xFFFF0000; 
    // D22 aus
    GPIOD->BSRR = (0x01 << (22 + 16)); 
    // D23 aus
    GPIOD->BSRR = (0x01 << (23 + 16)); 
    // D21 aus
    GPIOD->BSRR = (0x01 << (21 + 16));
    //StepCounter wieder auf den Ursprungswert
    nextStepCounter = 8;
}


void ledDirection(int direction) {
    if (direction == 0) { // rechts
        // D23 an
        GPIOD->BSRR = (0x01 << (23)); 
        // D22 aus
        GPIOD->BSRR = (0x01 << (22 + 16)); 
    } else if (direction == 1) { // links
        // D22 an
        GPIOD->BSRR = (0x01 << (22)); 
        // D23 aus
        GPIOD->BSRR = (0x01 << (23 + 16)); 
    } else {
        // D22 aus
        GPIOD->BSRR = (0x01 << (22 + 16)); 
        // D23 aus
        GPIOD->BSRR = (0x01 << (23 + 16)); 
    }
}


void ledError() {
    // D21 an
    GPIOD->BSRR = (0x01 << (21)); 
}


