
#ifndef IMAGEOPERATIONS
#define IMAGEOPERATIONS

#include "BMP_types.h"
#include "bmp.h"

/**
 * @brief waiting for button press to get next image
 */
void waitForButtonPress(void);


/**
 * @brief displays image on LCD-display
 * @param bmp Pointer to BMPImage
 * @return EOK oder NOK
 */
int displayBMP(BMPImage *bmp); 


#endif