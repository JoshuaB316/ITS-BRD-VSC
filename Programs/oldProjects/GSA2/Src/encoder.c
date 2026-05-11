/**
  * @file encoder.c
  * @author MJ
  * @date Nov 2025
  */

#include "encoder.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdio.h>
#include "errorManager.h"

#define IDR_MASK_CHANNEL_A (0x01 << (0)) // Pin A auf bit 0
#define IDR_MASK_CHANNEL_B (0x01 << (1)) // Pin B auf bit 1


bool givePinA(void){
    // lesen von Kanal A 
    if (IDR_MASK_CHANNEL_A == (GPIOF -> IDR & IDR_MASK_CHANNEL_A)){
        return true;
    } else {
        return false;
    }
}

bool givePinB(void){
    // lesen von Kanal B
   if (IDR_MASK_CHANNEL_B == (GPIOF -> IDR & IDR_MASK_CHANNEL_B)){
        return true;
    } else {
        return false;
    }
}

int getPhase(bool A, bool B) {
    if (!A && !B) {
        return 0; // phase a
    } else if (A && !B) {
        return 1; // phase b
    } else if (A && B) {
        return 2; // phase c
    } else { // (!A && B)
        return 3; // phase d
    }
}

int getDirection(int lastPhase, int currentPhase) {
    if (lastPhase == currentPhase) {
        return 2; // kein Phasenwechsel
    }

    if ((lastPhase == 0 && currentPhase == 1) ||
        (lastPhase == 1 && currentPhase == 2) ||
        (lastPhase == 2 && currentPhase == 3) ||
        (lastPhase == 3 && currentPhase == 0)) {
        return 0; // Phasenwechsel nach rechts
    } else if ((lastPhase == 0 && currentPhase == 3) ||
               (lastPhase == 3 && currentPhase == 2) ||
               (lastPhase == 2 && currentPhase == 1) ||
               (lastPhase == 1 && currentPhase == 0)) {
        return 1; // Phasenwechsel nach links
    } else {
        return -1; // Fehler beim Phasenwechsel
    }
}