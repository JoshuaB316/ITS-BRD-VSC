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

int nextStepCounter = 0;


void ledNextStep() {
    // alle LEDs aus
    GPIOD->BSRR = 0xFFFF0000; 

    // schaltet nächste LED an
    GPIOD->BSRR = (0x01 << (nextStepCounter)); 
    nextStepCounter += 1;

    // zurücksetzen auf erste LED wenn die Letzte erreicht wurde
    if (nextStepCounter > 7) {
        nextStepCounter = 0; 
    }
}


void ledReset() {
    // alle LEDs aus
    GPIOD->BSRR = 0xFFFF0000; 
    // D22 aus
    GPIOE->BSRR = (0x01 << (6 + 16)); 
    // D23 aus
    GPIOE->BSRR = (0x01 << (7 + 16)); 
    // D21 aus
    GPIOE->BSRR = (0x01 << (5 + 16));
    //StepCounter wieder auf den Ursprungswert
    nextStepCounter = 8;
}


void ledDirection(int direction) {
    if (direction == 0) { // rechts
        // D23 an
        GPIOE->BSRR = (0x01 << (7)); 
        // D22 aus
        GPIOE->BSRR = (0x01 << (6 + 16)); 
    } else if (direction == 1) { // links
        // D22 an
        GPIOE->BSRR = (0x01 << (6)); 
        // D23 aus
        GPIOE->BSRR = (0x01 << (7 + 16)); 
    } else {
        // D22 aus
        GPIOE->BSRR = (0x01 << (6 + 16)); 
        // D23 aus
        GPIOE->BSRR = (0x01 << (7 + 16)); 
    }
}



void ledError() {
    // D21 an
    GPIOE->BSRR = (0x01 << (5)); 
}


