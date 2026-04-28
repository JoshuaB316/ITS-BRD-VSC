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
#include "errorhaendler.h"

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
				clearStdout();
				value = t.val;
				break;

			case PLUS:
				clearStdout();
				add();
				break;

			case MINUS:
				clearStdout();
				subtract();
				break;

			case MULT:
				clearStdout();
				multiply();
				break;

			case DIV:
				clearStdout();
				divide();
				break;

			case PRT:
				clearStdout();
				p();
				break;

			case SWAP:
				clearStdout();
				r();
				break;

			case PRT_ALL:
				clearStdout();
				P();
				break;

			case CLEAR:
				clearStdout();
				C();
				break;

			case DOUBLE:
				clearStdout();
				push(value);	
				//d();
				break;
			case ENTER:
				//push(value);
				break;

			case UNEXPECTED:
				clearStdout();
				displayError(UnexpectedToken);
				break;

			case OVERFLOW:
				clearStdout();
				displayError(StackOverflow);
				break;

			default:
				clearStdout();
				displayError(UnknownToken);
				break;
		}
	}
}

// EOF
