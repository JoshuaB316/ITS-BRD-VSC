/**
  * @file display.c
  * @author MJ
  * @date Nov 2025
  */

#include "display.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "encoder.h"
#include "led_control.h"
#include <stdbool.h>
#include <stdio.h>



void display_update() {}
    


void display_error() {
    // Fehlermeldung auf bem Bildschirm
    lcdClearScreen();
    lcdPrintlnS("Fehler erkannt!");
    lcdPrintlnS("Bitte S6 drücken");
}