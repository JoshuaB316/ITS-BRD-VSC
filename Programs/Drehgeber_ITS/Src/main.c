/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor f�r technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    2020-08-23
 * @brief   L�sung GSP Drehgeber Polling
 ******************************************************************************
 */

#include "LCD_Demos.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "error.h"
#include "fontsFLASH.h"
#include "init.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "TFTOutput.h"
#include "fsm.h"
#include "input.h"
#include "output.h"
#include "timecalc.h"
#include "update.h"

#define UPDATE_TFT_INTERVAL                                                    \
  (250 * 1000) // minimal interval for TFT upate (in us)

/*
 *    E i n i g e  t y p i s c h e  Z e i t e n
 *
 *  - Ein Durchlauf der Super-Loop ohne Ausgabe eine Zeichens liegt bei 115 us
 *    Dabei kostet das sprintf mit zwei double Zahlen die meiste Zeit mit ca
 * 95us
 *
 *  - Die Ausgabe eines Zeichens auf dem Bildschirm dauert ca 860 us
 *  - Die Ausgabe aller Zeichen auf einen Schlag dauert 34 ms
 *
 *  - Formeln
 *    0.3�   = 1 tick/Phasewechsel
 *    1�     = 10/3 tick
 *
 *    Berechnen aus dem Abstand d zwischen zwei Ticks die Winkelgeschwindigkeit
 * v in �/s
 *
 *      d [s] / 1 [tick] = 1 [s] / y [ticks]
 *      d [s/tick] = 1/y [s/tick]
 *
 *      y [ticks/s] = 1/d [tick/s]
 *
 *      v [�/s] = 0.3 [�/tick] /d [ticks/s] = 0.3/d [�/s]
 *
 *  - Winkelgeschwindigkeit      Abstand zwischen zwei Phase
 *        0.3/d �/s                       d s
 *        37500 �/s                       8 us
 *          375 �/s                     800 us
 *            2 �/s                     150 ms
 *            1 �/s                     300 ms
 *          8.8 �/s                      34 ms
 *            8 �/s                    37,5 ms
 *            9 �/s                   33,33 ms
 *           10 �/s                      30 ms
 */

int main(void) {
  initITSboard(); // Initialisierung des ITS Boards
  GUI_init(500 +
           DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  if (!checkVersionFlashFonts()) {
    // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
    Error_Handler();
  }
  initTimeCalc();
  setupTerm();
  initFSM(giveCurrentPhase());
  initUpdate();

  double curAngle = getAngle();
  double curAngularSpeed = getAngularSpeed();
  fillResultBuffer(curAngle, curAngularSpeed);

  // super loop based on direct digital control (DDC)
  while (1) {
    // sample RT entities - read input
    setLED_GPIOG_2(false);
    bool errorReset = errorResetButtonPressed();
    setLED_GPIOG_2(true);
    PhaseType curPhase = giveCurrentPhase();
    uint32_t curTs = currentTimeStamp();

    // execution of control algorithm
    if (errorReset) { // reset - independent of current state
      resetFSM();
      initUpdate();
    }
    // execute FSM
    changeState(curPhase, curTs);
    updateUpdate();

    // calculate new set points for actors (new values for LEDs)
    uint8_t LEDscounterOutput = (uint8_t)getPhaseCount(
        NULL); // just output lowest 8 bit, independ of sign etc.
    bool LEDbackwardDirection = backwardRotation();
    bool LEDforwardDirection = forwardRotation();
    bool LEDerr = inErrorState();

    double newAngle = getAngle();
    double newAngularSpeed = getAngularSpeed();
    if ((curAngle != newAngle) || (curAngularSpeed != newAngularSpeed)) {
      curAngle = newAngle;
      curAngularSpeed = newAngularSpeed;
      fillResultBuffer(curAngle, curAngularSpeed);
    }
    // output set points to actors (set LEDs)
    setCounterLEDs(LEDscounterOutput);
    setForwardLED(LEDforwardDirection);
    setBackwardLED(LEDbackwardDirection);
    setErrorLED(LEDerr);
    printResultBuffer();
  } // End of super loop
  // This point will never be reached
}

// EOF