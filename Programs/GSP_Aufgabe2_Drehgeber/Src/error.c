/**
  * @file error.c
  * @author MJ
  * @date Nov 2025
  */

#include "error.h"
#include "stm32f4xx_hal.h"
#include "lcd.h"
#include "encoder.h"
#include "led_control.h"
#include "display.h"

#define GPIOF_PORT GPIOF

void reset() {
    //Kanäle zurücksetzen ??? benlötigt ?

    //Winkelwerte zurücksetzen


    //Anzeige auf dem ITSBoard zurücksetzen

    //LEDs zurücksetzen
    ledReset();

    //Display zurücksetzen
    display_update();
