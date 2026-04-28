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
	int errorHappened = 0;

	// Test in Endlosschleife
	while(1) {
		//HAL_Delay(10000);
		
		T_token  t = nextToken();

		if(errorHappened != 0){
			if(t.tok == CLEAR){
				clearStdout();
				errorHappened = 0;
				errNo = C();
				break;
			}
		}
		else {
			switch (t.tok) {
				case NUMBER:
					clearStdout();
					value = t.val;
					push(value);
					break;

				case PLUS:
					clearStdout();
					errNo = add();
					break;

				case MINUS:
					clearStdout();
					errNo = subtract();
					break;

				case MULT:
					clearStdout();
					errNo = multiply();
					break;

				case DIV:
					clearStdout();
					errNo = divide();
					break;

				case PRT:
					clearStdout();
					errNo = p();
					break;

				case SWAP:
					clearStdout();
					errNo = r();
					break;

				case PRT_ALL:
					clearStdout();
					errNo = P();
					break;

				case CLEAR:
					clearStdout();
					errNo = C();
					break;

				case DOUBLE:
					clearStdout();
					//push(value);	
					errNo = d();
					break;
				case ENTER:
					//push(value);
					break;

				case UNEXPECTED:
					clearStdout();
					errNo = UnexpectedToken;
					break;

				case OVERFLOW:
					clearStdout();
					errNo = StackOverflow;
					break;

				default:
					clearStdout();
					errNo = UnknownToken;
					break;
			}
		}

		switch (errNo){
			case StackOverflow:{
				displayError(StackOverflow);
				errorHappened = 1;
				break;
			}
			case StackUnderflow:{
				displayError(StackUnderflow);
				errorHappened = 1;
				break;
			}
			case IntOverflow:{
				displayError(IntOverflow);
				errorHappened = 1;
				break;
			}
			case IntUnderflow:{
				displayError(IntUnderflow);
				errorHappened = 1;
				break;
			}
			case DivideByZero:{
				displayError(DivideByZero);
				errorHappened = 1;
				break;
			}
			case UnexpectedToken:{
				displayError(UnexpectedToken);
				errorHappened = 1;
				break;
			}
			case UnknownToken:{
				displayError(UnknownToken);
				errorHappened = 1;
				break;
			}
			case EmptyStack:{
				displayError(EmptyStack);
				errorHappened = 1;
				break;
			}
			case NotEnoughElements:{
				displayError(NotEnoughElements);
				errorHappened = 1;
				break;
			}
		}



	}
}

// EOF
