/**
  * @file output.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header file of  output module. 
  */

#ifndef _OUTPUT_H
#define _OUTPUT_H

#include <stdint.h>
#include <stdbool.h>

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die 8 LEDs zur Ausgabe des Pulszaehlers.
 *
 *  @param  val Bitmuster, das ausgegeben wird.
 *
 *  @return void
 ****************************************************************************************/
void setCounterLEDs(const uint8_t val) ;

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die Error-LED.
 *
 *  @param  on <=> Error-LED wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setErrorLED   (bool on);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die LED zur Anzeige der Drehrichtung vorwerts.
 *
 *  @param  on <=> Forward-LED wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setForwardLED (bool on);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die LED zur Anzeige der Drehrichtung rueckwerts.
 *
 *  @param  on <=> Backward-LED wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setBackwardLED(bool on);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion set LED1 zur Zeitmessung.
 *
 *  @param  on <=> LED1 wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setLED_GPIOG_1(bool on);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion set LED2 zur Zeitmessung.
 *
 *  @param  on <=> LED2 wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setLED_GPIOG_2(bool on);

#endif
//EOF
