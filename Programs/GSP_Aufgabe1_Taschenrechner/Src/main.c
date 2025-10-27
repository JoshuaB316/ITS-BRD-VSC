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
#include "calculate.h"
#include "operations.h"
#include "toString.h"
#include "token.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	// Test in Endlosschleife
	while(1) {
		HAL_Delay(10000);

		switch(nextToken()) {
			case 'n':{
				push();
			}
			case '+';{
				add();
			}
			case '-';{
				subtract();
			}
			case '*';{
				multiply();
			}
			case '/';{
				divide();
			}
			case 'p';{
				p();
			}
			case 'P';{
				P();
			}
			case 'C';{
				C();
			}
			case 'd';{
				d();
			}
			case 'r';{
				r();
			}
			case ' ';{
				//ENTER
			}
			case 'U';{
				//UNEXPECTED
			}
			case 'O';{
				//OVERFLOW
			}

		}

	}
}

// EOF
