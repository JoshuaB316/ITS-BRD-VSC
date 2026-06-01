/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "input.h"
#include "errorhandler.h"
#include "bmp.h"
#include "perftimer.h"




int main(void) {
    // Initialisierung des ITS Boards
    initITSboard();
    
    // Initialisierung des LCD Displays
    GUI_init(DEFAULT_BRIGHTNESS);
    TP_Init(false);
    
    // Initialisierung der Eingabe (USB-UART Kommunikation)
    initInput();
    
    // Initialisierung Performance-Timer
    initPerfTimers();
    
    // Begrüßung
    GUI_clear();
    lcdGotoXY(1, 1);
    lcdPrintlnS("BMP Image Viewer");
    lcdPrintlnS("Waiting for images...");
    HAL_Delay(2000);
    
    // Hauptschleife - verarbeite Bilder nacheinander
    while (1) {
        // Lösche Display
        GUI_clear();
        lcdGotoXY(1, 1);
        lcdPrintlnS("Loading next image...");
        
        // Öffne nächste Datei
        openNextFile();
        
        // Erstelle BMP-Struktur
        BMPImage bmp;
        
        // Initialisiere BMP
        if (EOK != BMP_Init(&bmp)) {
            lcdGotoXY(1, 1);
            lcdPrintS("Error: BMP initialization failed");
            HAL_Delay(3000);
            continue;
        }
        
        // Lese und validiere Header
        if (EOK != BMP_ReadHeaders(&bmp)) {
            lcdGotoXY(1, 1);
            lcdPrintS("Error: Invalid BMP headers");
            HAL_Delay(3000);
            BMP_Cleanup(&bmp);
            continue;
        }
        
        // Lese Palette (falls nötig)
        if (EOK != BMP_ReadPalette(&bmp)) {
            lcdGotoXY(1, 1);
            lcdPrintS("Error: Failed to read palette");
            HAL_Delay(3000);
            BMP_Cleanup(&bmp);
            continue;
        }
        
        // Lösche Display und gebe Bild aus
        GUI_clear();
        
        if (EOK != displayBMP(&bmp)) {
            lcdGotoXY(1, 1);
            lcdPrintS("Error: Failed to display image");
            HAL_Delay(3000);
        }
        
        // Cleanup
        BMP_Cleanup(&bmp);
        
        // Warte auf Button-Druck für nächstes Bild
        waitForButtonPress();
    }
    
    return 0;
}

// EOF
