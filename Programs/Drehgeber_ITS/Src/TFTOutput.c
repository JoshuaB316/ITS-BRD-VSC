/**
  * @file TFTOutput.c
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief This modules implements a simple output to TFT monitor.
  *        It defines one TFT terminal areas. 
  *
  */
	
#include "TFTOutput.h"
#include <stdlib.h>
#include <stdio.h>
#include "output.h"
#include "terminal.h"
#include "LCD_GUI.h"
#include "fontsFLASH.h"

// Definition of terminal area
#define ROW_1				       2
#define ROW_2				       5
#define COL_1				       3
#define COL_2				       (19 + (COL_1))

#define SPACE_4_NUMBERS		    12

#define OUT_STR_SIZE           32

static Terminal term;

void setupTerm(void) {
	// For speeding up TFT display only numbers will be updated.
	Coordinate tl = {0,0};
	Coordinate br = {LCD_WIDTH-1, LCD_HEIGHT-1};
   term = genTerm(tl, br, BLUE, YELLOW, &Font16FLASH);

	setPosTerm(ROW_1, COL_1, &term);
	printTerm("Winkel          :              Grad",   &term);
	setPosTerm(ROW_2, COL_1, &term);
	printTerm("Geschwindigkeit :              Grad/s", &term);
   setTextColorTerm(RED, &term); // Color for numbers
}

/* Das printResults kostet die meiste Zeit aufgrund der Ansteuerung des TFT Displays
 * Die Zeit steigt in erster Naeherung linear zur Anzahl der Zeichen, die auf dem
 * Bildschirm dargestellt werden.
 *
 * Konsequenz: In jedem Durchlauf der Super Loop wird maximal ein Zeichen auf dem
 * Bildschirm ausgegeben. Somit wird die maximale Drehgeschwindigkeit erhöht, denn
 * diese wird durch die maximale Länge Durchlaufs durch die Super Loop begrenzt.
 * Diese Optimierung wird ueber folgende Prepozessor Variable aktiviert.
 */

#define PRINT_STEP_BY_STEP     # Zeichenweise Ausgabe

static char angleBuffer[OUT_STR_SIZE] = {'\0'};
static char speedBuffer[OUT_STR_SIZE] = {'\0'};
static char *nextBufferToPrint = NULL;     // NULL : Es liegt keine neue Ausgabe vor
static int nextPosToPrint = 0;

/*
 * @brief This function converts an double to a str with one position after decimal point.
 */

static void double2str(char * buf, const int buf_size, double val){
	char *formatStr = "%-20.1lf";
   
   snprintf(buf, buf_size , formatStr, val);
   // Fuelle den String mit Blanks auf, damit alte Werte auf der Ausgabe ueberschrieben werden
	 for(int i = 0; (i < SPACE_4_NUMBERS-1) && (i < (buf_size-1)); i++) {
		  if (buf[i] == '\0') {
				 buf[i] = ' '; 
				 buf[i+1] = '\0'; 
			}
	 }	
}

void fillResultBuffer(double angle, double angularSpeed){
   double2str(angleBuffer, sizeof(angleBuffer), angle);
   double2str(speedBuffer, sizeof(speedBuffer), angularSpeed);
   nextBufferToPrint = angleBuffer;
   nextPosToPrint = 0;
}

#ifdef PRINT_STEP_BY_STEP

static void printResultBufferStepByStep(void){
	if (nextBufferToPrint == NULL) { // Alle Zeichen wurden schon ausgegeben
      return;
   }
   // Geben neachsten Zeichen aus
	if (nextBufferToPrint[nextPosToPrint] == '\0'){ 
	   if (nextBufferToPrint == speedBuffer){ // alle Zeichen ausgegeben
		 	nextBufferToPrint = NULL;
			return;
		}
		nextBufferToPrint = speedBuffer;
		nextPosToPrint = 0;	 
	}   
	setPosTerm((nextBufferToPrint == angleBuffer) ? ROW_1: ROW_2, 
	            COL_2 + nextPosToPrint, &term);
	char b[] = {nextBufferToPrint[nextPosToPrint++] , '\0'};
	printTerm(b, &term);
}

void printResultBuffer(void){
	printResultBufferStepByStep();
}
#else
void printResultBuffer(void){
   if (nextBufferToPrint != NULL){
		// Neue Ausgabe liegt vor. Geben alle Zeichen auf einmal aus.
	   setPosTerm(ROW_1, COL_2, &term);
		printTerm(angleBuffer, &term);
		setPosTerm(ROW_2, COL_2, &term);
      printTerm(speedBuffer, &term);
		nextBufferToPrint = NULL;
   }
}
#endif

// EOF
