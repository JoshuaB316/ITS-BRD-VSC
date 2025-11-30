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
#include "scanner.h"
#include "stack.h"
#include "display.h"
#include <stdio.h>

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	initDisplay();
  // Begruessungstext	
	//lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	int value = 0;

	// Test in Endlosschleife
	while(1) {
		//HAL_Delay(10000);
		
		T_token  t = nextToken();

		switch (t.tok) {
			case NUMBER:
				value = t.val;
				break;

			case PLUS:
				add();
				break;

			case MINUS:
				subtract();
				break;

			case MULT:
				multiply();
				break;

			case DIV:
				divide();
				break;

			case PRT:
				p();
				break;

			case SWAP:
				r();
				break;

			case PRT_ALL:
				P();
				break;

			case CLEAR:
				C();
				break;

			case DOUBLE:
			push(value);	
			//d();
				break;

			case ENTER:
				//push(value);
				break;

			case UNEXPECTED:
				printStdout("Unexpected token!\n");
				break;

			case OVERFLOW:
				printStdout("Stack overflow!\n");
				break;

			default:
				printStdout("Unknown token!\n");
				break;
		}
	}
}

// EOF
