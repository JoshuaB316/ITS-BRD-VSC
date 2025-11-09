/**
  * @file led_control.h
  * @author MJ
  * @date Nov 2025
  */

#ifndef LED_CONTROL_H
#define LED_CONTROL_H


/*
 ****************************************************************************************
 *  @brief      Steuerung der LEDs entsprechend der Phasen
 *
 *  @return     void 
 ****************************************************************************************/
void led_steps();

/*
 ****************************************************************************************
 *  @brief      Steuerung der LEDs entsprechend der Drehrichtung
 *
 *  @return     void 
 ****************************************************************************************/
void led_direction();

/*
 ****************************************************************************************
 *  @brief      Steuerung der LEDs im Fehlerfall
 *
 *  @return     void 
 ****************************************************************************************/
void led_error();

/* Wieso haben wir so viele LEDs für die Phasenanzeige ? 
*  
*/



#endif