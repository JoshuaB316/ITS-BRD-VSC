/**
  * @file led_control.h
  * @author MJ
  * @date Nov 2025
  */

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

/**
 * @brief schlaltet nächste LED an und schaltet die alte aus
 * 
 */
void ledNextStep();

/**
 * @brief setzt dei LED auf ausgangseinstellung zurück
 * 
 */
void ledReset();

/**
 * @brief schaltet D23 and wenn Laufrichtung rechts und D22 wenn Laufrichtung links
 * @param direction Laufrichtung benötigt
 */
void ledDirection(int direction);

/**
 * @brief schaltet D21 an wenn ein Fehler vorliegt
 * 
 */
void ledError();


#endif