#include "bmp.h"
#include "input.h"
#include "errorhandler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int rleMode;        // 0 = normal, 1 = in RLE sequenz
    int rleCount;       // Verbleibende pixel in RLE sequenz
    uint8_t rleValue;   // Farbindex für RLE
    int rleAbsCount;    // Verbleibende bytes in absolute modus
    int linePixels;     // Pixel lesen in momentaner zeile
} RLEState;

// alle Werte mit 0 initialisierung
static RLEState rleState = {0};


int BMP_Init(BMPImage *bmp) {
    ERR_HANDLER(NULL == bmp, "BMP_Init: bmp pointer ist NULL");
    
    memset(bmp, 0, sizeof(BMPImage));
    bmp->palette = NULL;
    bmp->paletteSize = 0;
    bmp->currentLine = 0;
    bmp->pixelsRead = 0;
    memset(&rleState, 0, sizeof(RLEState));
    
    return EOK;
}


int BMP_ReadHeaders(BMPImage *bmp) {
    ERR_HANDLER(NULL == bmp, "BMP_ReadHeaders: bmp pointer ist NULL");
    
    // BITMAPFILEHEADER lesen fileHeader
    RETURN_NOK_ON_ERR(1 != COMread((char*)&bmp->fileHeader, sizeof(BITMAPFILEHEADER), 1), "BMP_ReadHeaders: Error beim lesen von BITMAPFILEHEADER");
    
    // valide signatur?
    ERR_HANDLER(BMP_SIGNATURE != bmp->fileHeader.bfType, "BMP_ReadHeaders: Invalide BMP Signatur");
    
    // reservierte Felder überprüfen
    ERR_HANDLER(0 != bmp->fileHeader.bfReserved1, "BMP_ReadHeaders: bfReserved1 sollte 0 sein");
    ERR_HANDLER(0 != bmp->fileHeader.bfReserved2, "BMP_ReadHeaders: bfReserved2 sollte 0 sein");
    
    // BITMAPINFOHEADER lesen infoHeader
    RETURN_NOK_ON_ERR(1 != COMread((char*)&bmp->infoHeader, sizeof(BITMAPINFOHEADER), 1), "BMP_ReadHeaders: Error beim lesen von BITMAPINFOHEADER");
    
    // infoHeader größe überprüfen ob richtiges Format
    ERR_HANDLER(0x28 != bmp->infoHeader.biSize, "BMP_ReadHeaders: Invalide biSize");
    
    // bitCount überprüfen nur 8 und 24 werden unterstützt
    ERR_HANDLER((bmp->infoHeader.biBitCount != 8) && (bmp->infoHeader.biBitCount != 24), "BMP_ReadHeaders: Nur 8-bit und 24-bit BMPs werden unterstützt");
    
    // überprüfen ob 1 bild
    ERR_HANDLER(1 != bmp->infoHeader.biPlanes, "BMP_ReadHeaders: biPlanes müssen immer 1 sein");
    
    // unterstützte Kompressionen überprüfen
    ERR_HANDLER((bmp->infoHeader.biCompression != BI_RGB) && (bmp->infoHeader.biCompression != BI_RLE8), 
                "BMP_ReadHeaders: Nur BI_RGB und BI_RLE8 kompressione werden unterstützt");
    
    // RLE8 ist nur für reine 8 bit Bilder geeignet
    ERR_HANDLER((BI_RLE8 == bmp->infoHeader.biCompression) && (8 != bmp->infoHeader.biBitCount),
                "BMP_ReadHeaders: BI_RLE8 nur für 8-bit Bilder");
    
    return EOK;
}


int BMP_ReadPalette(BMPImage *bmp) {
    ERR_HANDLER(NULL == bmp, "BMP_ReadPalette: bmp pointer ist NULL");
    
    // nur 8 bit Bilder haben Paletten
    if (8 != bmp->infoHeader.biBitCount) {
        return EOK;
    }
    
    // Palettengröße bestimmen
    if (0 != bmp->infoHeader.biClrUsed) {
        bmp->paletteSize = bmp->infoHeader.biClrUsed;
    } else {
        bmp->paletteSize = MAX_COLOR_TABLE_SIZE;
    }
    
    // Speicher für die Palette einrichten
    bmp->palette = (RGBQUAD *)malloc(bmp->paletteSize * sizeof(RGBQUAD));
    ERR_HANDLER(NULL == bmp->palette, "BMP_ReadPalette: Speicherreservierung fehlgeschlagen");
    
    // Palette Lesen
    RETURN_NOK_ON_ERR(bmp->paletteSize != COMread((char*)bmp->palette, sizeof(RGBQUAD), bmp->paletteSize), "BMP_ReadPalette: Error reading palette");
    return EOK;
}


uint16_t BMP_RGBQuadToRGB565(RGBQUAD *rgb) {
    if (NULL == rgb) return 0;
    
    uint8_t r = rgb->rgbRed;
    uint8_t g = rgb->rgbGreen;
    uint8_t b = rgb->rgbBlue;
    
    // 8-bit zu 5-bit konvertieren
    uint16_t r5 = (r >> 3) & 0x1F;
    uint16_t g6 = (g >> 2) & 0x3F;
    uint16_t b5 = (b >> 3) & 0x1F;
    
    // RGB565
    uint16_t rgb565 = (r5 << 11) | (g6 << 5) | b5;
    
    return rgb565;
}


uint16_t BMP_RGBTripleToRGB565(RGBTRIPLE *rgb) {
    if (NULL == rgb) return 0;
    
    uint8_t r = rgb->rgbtRed;
    uint8_t g = rgb->rgbtGreen;
    uint8_t b = rgb->rgbtBlue;
    
    // 8-bit to 5-bit konvertieren
    uint16_t r5 = (r >> 3) & 0x1F;
    uint16_t g6 = (g >> 2) & 0x3F;
    uint16_t b5 = (b >> 3) & 0x1F;
    
    // RGB565
    uint16_t rgb565 = (r5 << 11) | (g6 << 5) | b5;
    
    return rgb565;
}


uint16_t BMP_PaletteIndexToRGB565(BMPImage *bmp, uint8_t index) {
    if ((NULL == bmp) || (NULL == bmp->palette)) return 0;
    if (index >= bmp->paletteSize) return 0;
    
    return BMP_RGBQuadToRGB565(&bmp->palette[index]);
}


static int RLE_ReadNextByte(uint8_t *byte) {
    int c = nextChar();
    if (EOF == c) return EOF;
    *byte = (uint8_t)c;
    return EOK;
}


static int RLE_GetNextPixel(BMPImage *bmp, uint8_t *pixelIndex) {
    uint8_t byte1, byte2;
    
    while (1) {
        // wenn noch pixel in RLE sequenz
        if (rleState.rleCount > 0) {
            *pixelIndex = rleState.rleValue;
            rleState.rleCount--;
            rleState.linePixels++;
            return EOK;
        }
        
        // wenn es noch bytes im absoluten modus gibt
        if (rleState.rleAbsCount > 0) {
            RETURN_NOK_ON_ERR(EOF == RLE_ReadNextByte(pixelIndex), "RLE_GetNextPixel: Unerwartetes EOF im absoluten modus");
            rleState.rleAbsCount--;
            rleState.linePixels++;
            
            
        // rleAbsCount == 0 , Absolute Mode fertig!
        if (0 == rleState.rleAbsCount) {
            // Bei ungerader Anzahl Bytes → 1 Padding-Byte lesen
            if (byte2 % 2 != 0) {
                uint8_t dummy;
                RLE_ReadNextByte(&dummy);
            }
        }

            return EOK;
        }
        
        // nächster RLE befehl
        RETURN_NOK_ON_ERR(EOF == RLE_ReadNextByte(&byte1), "RLE_GetNextPixel: Unerwartetes EOF");
        RETURN_NOK_ON_ERR(EOF == RLE_ReadNextByte(&byte2), "RLE_GetNextPixel: Unerwartetes EOF");
        
        // escape sequenz
        if (0 == byte1) {
            if (0 == byte2) {
                // Ende der Linie
                rleState.linePixels = 0;
                continue;
            } else if (1 == byte2) {
                // Ende der bitmap
                return EOF;
            } else if (2 == byte2) {
                // Delta = Springe zu einer anderen Position im Bild
                uint8_t dx, dy;
                RLE_ReadNextByte(&dx);
                RLE_ReadNextByte(&dy);
                continue;
            } else {
                // Absolute modus (byte2 = nummer der pixel)
                rleState.rleAbsCount = byte2;
                rleState.linePixels = 0;
                continue;
            }
        }
        
        // byte1 = count, byte2 = color index
        rleState.rleCount = byte1;
        rleState.rleValue = byte2;
        rleState.linePixels = 0;
    }
}


int BMP_GetNextPixel(BMPImage *bmp, uint16_t *pixel) {
    ERR_HANDLER(NULL == bmp, "BMP_GetNextPixel: bmp pointer ist NULL");
    ERR_HANDLER(NULL == pixel, "BMP_GetNextPixel: pixel pointer ist NULL");
    
    int result;
    
    if (BI_RLE8 == bmp->infoHeader.biCompression) {
        // RLE 8-bit kompression
        uint8_t pixelIndex;
        result = RLE_GetNextPixel(bmp, &pixelIndex);
        
        if (EOK == result) {
            *pixel = BMP_PaletteIndexToRGB565(bmp, pixelIndex);
            bmp->pixelsRead++;
            
            // Überprüfen ob Zeile fertig
            if (bmp->pixelsRead >= bmp->infoHeader.biWidth) {
                bmp->pixelsRead = 0;
                bmp->currentLine++;
            }
        }
        return result;
    } else if (8 == bmp->infoHeader.biBitCount) {
        // Uncompressed 8-bit mit palette
        uint8_t pixelIndex;
        int c = nextChar();
        
        if (EOF == c) return EOF;
        
        pixelIndex = (uint8_t)c;
        *pixel = BMP_PaletteIndexToRGB565(bmp, pixelIndex);
        bmp->pixelsRead++;
        
        // Überprüfen ob Zeile fertig (padding)
        if (bmp->pixelsRead >= bmp->infoHeader.biWidth) {
            // padding bytes berechnen
            int bytesPerLine = (((bmp->infoHeader.biWidth * 8) + 31) / 32) * 4;
            int usedBytes = bmp->infoHeader.biWidth;
            int paddingBytes = bytesPerLine - usedBytes;
            
            // padding bytes überspringen
            for (int i = 0; i < paddingBytes; i++) {
                nextChar();
            }
            
            bmp->pixelsRead = 0;
            bmp->currentLine++;
        }
        
        return EOK;
    } else if (24 == bmp->infoHeader.biBitCount) {
        // Uncompressed 24-bit
        RGBTRIPLE rgb;
        int c1 = nextChar();
        int c2 = nextChar();
        int c3 = nextChar();
        
        if ((EOF == c1) || (EOF == c2) || (EOF == c3)) return EOF;
        
        rgb.rgbtBlue = (uint8_t)c1;
        rgb.rgbtGreen = (uint8_t)c2;
        rgb.rgbtRed = (uint8_t)c3;
        
        *pixel = BMP_RGBTripleToRGB565(&rgb);
        bmp->pixelsRead++;
        
        // Überprüfen ob Zeile fertig (padding)
        if (bmp->pixelsRead >= bmp->infoHeader.biWidth) {
            // padding bytes berechnen
            int bytesPerLine = (((bmp->infoHeader.biWidth * 24) + 31) / 32) * 4;
            int usedBytes = bmp->infoHeader.biWidth * 3;
            int paddingBytes = bytesPerLine - usedBytes;
            
            // padding bytes überspringen
            for (int i = 0; i < paddingBytes; i++) {
                nextChar();
            }
            
            bmp->pixelsRead = 0;
            bmp->currentLine++;
        }
        
        return EOK;
    }
    
    return NOK;
}


void BMP_Cleanup(BMPImage *bmp) {
    if (NULL == bmp) return;
    
    if (NULL != bmp->palette) {
        free(bmp->palette);
        bmp->palette = NULL;
    }
    
    bmp->paletteSize = 0;
    memset(&rleState, 0, sizeof(RLEState));
}