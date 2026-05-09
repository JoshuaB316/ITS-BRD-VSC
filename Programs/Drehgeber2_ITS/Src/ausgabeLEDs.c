/** 
* @file ausgabeLEDs.c
* @author Esmat Rabaki, Raphael Pfeiffer
* @brief hier werden die LEDS ausgegeben und Taster S6 wird überprüft 
*/


#include "ausgabeLEDs.h"
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "error.h"


#define BSRR_MASK_PIN_23 (0x01U << 7)
#define BSRR_MASK_PIN_22 (0x01U << 6)
#define BSRR_MASKE_PIN_21 (0x01U << 5)
#define IDR_MASKE_PIN_6 (0x01U << 6)


/**
 * @brief Schaltet die LEDs entsprechend der übergebenen Maske ein oder aus.
 * @param led_mask Bitmaske, die angibt, welche LEDs geschaltet werden sollen.
 *@param richtung da wird entweder 1(vorwärts) oder -1(rückwärts) gegeben  
 */
void toggle_LEDs(uint32_t led_mask, int richtung) 
{   
    //von 32bit in 8 bit uwmandeln
    uint8_t mask = (uint8_t)led_mask;
    GPIOD->BSRR = (0x0F << 16);
    GPIOD->BSRR = mask;
    if (richtung ==1)
    {
        GPIOE->BSRR = BSRR_MASK_PIN_23; // LED 23 anschalten (vorwärts)
        GPIOE->BSRR = (BSRR_MASK_PIN_22 << 16); // LED 22 ausschalten
    }else {
        GPIOE->BSRR = BSRR_MASK_PIN_22; // LED 22 anschalten (rückwärts)
        GPIOE->BSRR = (BSRR_MASK_PIN_23 << 16); // LED 23 ausschalten (vorwärts)
    }
} 
/**
*@brief LED21 geht an, wenn es fehler bei der phasen auftreten
*/  
   void toggle_LEDs_Error(){
    GPIOE->BSRR = BSRR_MASKE_PIN_21; // LED 21 einschalten(fehler)  
    }
   void rest_LEDs_Error(){
    GPIOE->BSRR = BSRR_MASKE_PIN_21 << 16; // LED 21 einschalten(fehler)  
    }
/**
*@brief es wird überprüft, ob taster S6 gedrückt würde.
*
 */
bool readGPIOPIN ()
{
    return IDR_MASKE_PIN_6 != (GPIOF->IDR & IDR_MASKE_PIN_6);    
}



