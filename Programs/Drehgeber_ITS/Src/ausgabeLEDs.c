/**
* @file ausgabeLEDs.c
* @authors Mustafa Kocatürk, Joshua Beinert
* @date Mai 2026
*/


#include "ausgabeLEDs.h"
#include "error.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

#define BSRR_MASK_PIN_23 (0x01U << 7)
#define BSRR_MASK_PIN_22 (0x01U << 6)
#define BSRR_MASKE_PIN_21 (0x01U << 5)
#define IDR_MASKE_PIN_6 (0x01U << 6)

void toggleLEDs(uint32_t led_mask, int richtung) {
  // von 32bit in 8 bit uwmandeln
  uint8_t mask = (uint8_t)led_mask;
  GPIOD->BSRR = (0x0F << 16);
  GPIOD->BSRR = mask;
  if (richtung == 1) {
    GPIOE->BSRR = BSRR_MASK_PIN_23;         // LED 23 anschalten (vorwärts)
    GPIOE->BSRR = (BSRR_MASK_PIN_22 << 16); // LED 22 ausschalten
  } else {
    GPIOE->BSRR = BSRR_MASK_PIN_22;         // LED 22 anschalten (rückwärts)
    GPIOE->BSRR = (BSRR_MASK_PIN_23 << 16); // LED 23 ausschalten (vorwärts)
  }
}

void setErrorLED() {
  GPIOE->BSRR = BSRR_MASKE_PIN_21; // LED 21 einschalten(fehler)
}


void resetErrorLED() {
  GPIOE->BSRR = BSRR_MASKE_PIN_21 << 16; // LED 21 ausschalten(fehler)
}


bool readPinS6() {
  return IDR_MASKE_PIN_6 != (GPIOF->IDR & IDR_MASKE_PIN_6); 
}