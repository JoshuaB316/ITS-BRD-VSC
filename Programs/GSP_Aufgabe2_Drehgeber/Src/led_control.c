/**
  * @file led_control.c
  * @author MJ
  * @date Nov 2025
  */

#include "led_control.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

#define LED_PORT GPIOD
#define nextStepCounter 8


void ledNextStep() {
    
    GPIOD->BSRR = 0xFFFF0000; // alle LEDs aus

    GPIOD->BSRR = (0x01 << (nextStepCounter)); // setzt die nächste LED
    nextStepCounter++;

    if (nextStepCounter > 15) {
        nextStepCounter = 8; // zurücksetzen auf D8
    }
}


void ledReset() {
    GPIOD->BSRR = 0xFFFF0000; // alle LEDs aus
    nextStepCounter = 8;
}


void ledDirection(int direction) {
    if (direction == 0) {
        GPIOD->BSRR = (0x01 << (23)); // D23 an
        GPIOD->BSRR = (0x01 << (22 + 16)); // D22 aus
    } else if (direction == 1) {
        GPIOD->BSRR = (0x01 << (22)); // D22 an
        GPIOD->BSRR = (0x01 << (23 + 16)); // D23 aus
    } else {
        GPIOD->BSRR = (0x01 << (22 + 16)); // D22 aus
        GPIOD->BSRR = (0x01 << (23 + 16)); // D23 aus         
    }
}


void ledError() {
    GPIOD->BSRR = (0x01 << (21)); // D21 an
}


