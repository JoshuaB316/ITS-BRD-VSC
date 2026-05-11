/**
* @file     outputLEDs.c
* @authors  Mustafa Kocatürk, Joshua Beinert
* @date     Mai 2026
*/


#include "outputLEDs.h"
#include "error.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

#define BSRR_MASK_PIN_23 (0x01U << 7)
#define BSRR_MASK_PIN_22 (0x01U << 6)
#define BSRR_MASKE_PIN_21 (0x01U << 5)
#define IDR_MASKE_PIN_6 (0x01U << 6)


void toggleLEDs(uint32_t led_mask, int direction) {

  // von 32 bit in 8 bit uwmandeln (8 LEDs)
  uint8_t mask = (uint8_t)led_mask;
  GPIOD->BSRR = (0x0F << 16);
  GPIOD->BSRR = mask;
  if (direction == 1) {
    GPIOE->BSRR = BSRR_MASK_PIN_23;         // Vorwärts-LED 23 anschalten
    GPIOE->BSRR = (BSRR_MASK_PIN_22 << 16); // Rückwärts-LED 22 ausschalten
  } else {
    GPIOE->BSRR = BSRR_MASK_PIN_22;         // Rückwärts-LED 22 anschalten
    GPIOE->BSRR = (BSRR_MASK_PIN_23 << 16); // Vorwärts-LED 23 ausschalten
  }
}

void setErrorLED() {
  // Fehler-LED 21 einschalten
  GPIOE->BSRR = BSRR_MASKE_PIN_21; 
}

void resetErrorLED() {
  // Fehler-LED 21 ausschalten
  GPIOE->BSRR = BSRR_MASKE_PIN_21 << 16; 
}

bool readPinS6() {
  return IDR_MASKE_PIN_6 != (GPIOF->IDR & IDR_MASKE_PIN_6); 
}