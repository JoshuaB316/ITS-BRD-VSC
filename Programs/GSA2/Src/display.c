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
#include "errorManager.h"



void display_update() {
  // Winkel, Winkelgwschwindigkeit aber die einzelnen chars??
}
    


void display_error() {
  // Fehlermeldung auf bem Bildschirm
  LCD_clear();
  lcdPrintlnS("Fehler erkannt!");
  lcdPrintlnS("Bitte S6 drücken");
}