/**
  * @file output.c
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Dieses Modul treibt die GPIO Ausgaben. 
	*
  */

#include "output.h"
#include <stm32f4xx_hal.h>

#define LED_REG_COUNTER				 GPIOD
#define LED_REG_INFO  				 GPIOE

#define OFFSET_TIME_MEA_1			 1
#define OFFSET_TIME_MEA_2			 2

#define OFFSET_ERROR_LED			 5
#define OFFSET_BACKWARD_LED       6
#define OFFSET_FORWARD_LED		    7
#define OFFSET_COUNTER_LEDS       0

void setCounterLEDs(const uint8_t val) {
	 // read modify write required
	 const uint32_t mask = (0xFF << OFFSET_COUNTER_LEDS);
	 uint32_t  currentValue = LED_REG_COUNTER->ODR;
	 currentValue &= ~mask;
	 currentValue |= (((uint32_t) val) << OFFSET_COUNTER_LEDS);
	 LED_REG_COUNTER->ODR = currentValue;
}

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt einen Pins einer GPIO Ports.
 *
 *  @param  port Das GPIO Port, dessen veraendert wird
 *  @param  pin Nummer des Pins
 *  @param  switchOn <=> Der pin wird auf high gesetzt
 *
 *  @return void
 ****************************************************************************************/
static void setPin(GPIO_TypeDef *port, unsigned char pin, bool switchOn) {
   port->BSRR = (0x01 << (pin + (switchOn ? 0 : 16)));
}

void setErrorLED(bool on){
   setPin(LED_REG_INFO, OFFSET_ERROR_LED, on);
}

void setForwardLED(bool on){
   setPin(LED_REG_INFO, OFFSET_FORWARD_LED, on);
}

void setBackwardLED(bool on){
   setPin(LED_REG_INFO, OFFSET_BACKWARD_LED, on);
}

void setLED_GPIOG_1(bool on){
   setPin(LED_REG_INFO, OFFSET_TIME_MEA_1, on);
}

void setLED_GPIOG_2(bool on){
   setPin(LED_REG_INFO, OFFSET_TIME_MEA_2, on);
}

//EOF
