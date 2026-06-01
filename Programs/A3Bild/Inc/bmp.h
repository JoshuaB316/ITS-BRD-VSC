#ifndef _BMP_H
#define _BMP_H

#include "BMP_types.h"
#include "errorhandler.h"

/**
 * @brief Structure to hold BMP image information
 */
typedef struct {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD *palette;           // Farbpalette (nur bei 8-Bit)
    int paletteSize;            // Anzahl der Farben in der Palette
    int currentLine;            // Aktuelle Zeile beim Lesen
    int pixelsRead;             // Anzahl gelesener Pixel in aktueller Zeile
} BMPImage;

/**
 * @brief Initialize BMP image structure
 * @param bmp Pointer to BMPImage structure
 * @retval EOK or NOK
 */
int BMP_Init(BMPImage *bmp);

/**
 * @brief Read and validate BMP file headers
 * @param bmp Pointer to BMPImage structure
 * @retval EOK or NOK
 */
int BMP_ReadHeaders(BMPImage *bmp);

/**
 * @brief Read BMP palette (for 8-bit images)
 * @param bmp Pointer to BMPImage structure
 * @retval EOK or NOK
 */
int BMP_ReadPalette(BMPImage *bmp);

/**
 * @brief Get next pixel from BMP file
 * @param bmp Pointer to BMPImage structure
 * @param pixel Pointer to store 16-bit pixel value (RGB565)
 * @retval EOK (pixel read), NOK (error), or EOF
 */
int BMP_GetNextPixel(BMPImage *bmp, uint16_t *pixel);

/**
 * @brief Convert 8-bit palette index to 16-bit RGB565
 * @param bmp Pointer to BMPImage structure
 * @param index Palette index
 * @retval 16-bit RGB565 color value
 */
uint16_t BMP_PaletteIndexToRGB565(BMPImage *bmp, uint8_t index);

/**
 * @brief Convert RGBTRIPLE (24-bit) to 16-bit RGB565
 * @param rgb Pointer to RGBTRIPLE structure
 * @retval 16-bit RGB565 color value
 */
uint16_t BMP_RGBTripleToRGB565(RGBTRIPLE *rgb);

/**
 * @brief Convert RGBQUAD to 16-bit RGB565
 * @param rgb Pointer to RGBQUAD structure
 * @retval 16-bit RGB565 color value
 */
uint16_t BMP_RGBQuadToRGB565(RGBQUAD *rgb);

/**
 * @brief Cleanup BMP resources
 * @param bmp Pointer to BMPImage structure
 * @retval None
 */
void BMP_Cleanup(BMPImage *bmp);

#endif /* _BMP_H */
// EOF