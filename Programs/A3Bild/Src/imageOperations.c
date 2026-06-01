#include "imageOperations.h"
#include "BMP_types"


// LCD Display Dimensionen
#define LCD_WIDTH   480
#define LCD_HEIGHT  320

// Button für nächstes Bild
#define BUTTON_PIN  //definition
#define BUTTON_PORT //definition

static void waitForButtonPress() {
    lcdPrintlnS("Press button for next image!");
    
    // Einfache Button-Abfrage (polling)
    while (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_SET) {
        HAL_Delay(10);
    }
    
    // Entprellen
    HAL_Delay(50);
    
    while (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET) {
        HAL_Delay(10);
    }
    
    HAL_Delay(50);
}



static int displayBMP(BMPImage *bmp) {
    LOOP_ON_ERR(NULL == bmp, "displayBMP: bmp pointer is NULL");
    
    // Überprüfe Bildgröße
    if ((bmp->infoHeader.biWidth <= 0) || (bmp->infoHeader.biHeight <= 0)) {
        lcdGotoXY(1, 1);
        lcdPrintS("Error: Invalid image dimensions");
        return NOK;
    }
    
    // Berechne sichtbare Dimensionen (nicht größer als Display)
    int displayWidth = (bmp->infoHeader.biWidth > LCD_WIDTH) ? 
                       LCD_WIDTH : bmp->infoHeader.biWidth;
    int displayHeight = (bmp->infoHeader.biHeight > LCD_HEIGHT) ? 
                        LCD_HEIGHT : bmp->infoHeader.biHeight;
    
    // Gebe Bildinfo auf LCD aus
    lcdGotoXY(1, 1);
    char infoStr;
    snprintf(infoStr, sizeof(infoStr), 
             "Image: %ldx%ld, %d-bit, Comp: %ld",
             bmp->infoHeader.biWidth,
             bmp->infoHeader.biHeight,
             bmp->infoHeader.biBitCount,
             bmp->infoHeader.biCompression);
    lcdPrintS(infoStr);
    
    // Starte Performance-Timer
    startPerfTimer(0);
    
    // Lese und gebe Pixel aus
    uint16_t pixel;
    int pixelCount = 0;
    int errorCount = 0;
    
    for (int y = 0; y < displayHeight; y++) {
        for (int x = 0; x < displayWidth; x++) {
            // Lese nächsten Pixel
            int result = BMP_GetNextPixel(bmp, &pixel);
            
            if (EOF == result) {
                // Dateiende erreicht
                lcdGotoXY(1, 3);
                lcdPrintS("EOF reached");
                goto display_done;
            }
            
            if (NOK == result) {
                errorCount++;
                if (errorCount > 10) {
                    lcdGotoXY(1, 3);
                    lcdPrintS("Too many errors, aborting");
                    stopPerfTimer(0);
                    return NOK;
                }
                continue;
            }
            
            // Gebe Pixel auf Display aus
            // Beachte: BMP speichert Bilder von unten nach oben
            // LCD erwartet von oben nach unten
            int displayY = displayHeight - 1 - y;
            GUI_drawPoint(x, displayY, pixel, DOT_PIXEL_1X1, DOT_FILL_AROUND);
            
            pixelCount++;
            
            // Fortschritt anzeigen (alle 1000 Pixel)
            if (0 == (pixelCount % 1000)) {
                lcdGotoXY(1, 2);
                char progStr;
                snprintf(progStr, sizeof(progStr), "Pixels: %d", pixelCount);
                lcdPrintS(progStr);
            }
        }
    }
    
display_done:
    stopPerfTimer(0);
    
    // Gebe Statistik aus
    lcdGotoXY(1, 4);
    char statStr;
    snprintf(statStr, sizeof(statStr), "Displayed: %d pixels", pixelCount);
    lcdPrintS(statStr);
    
    return EOK;
}