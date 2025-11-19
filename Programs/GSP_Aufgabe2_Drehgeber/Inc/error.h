/**
  * @file error.h
  * @author MJ
  * @date Nov 2025
  */

#ifndef ERROR_H
#define ERROR_H

// Variablen für Winkel
extern double angle;
extern double angleSpeed;
extern double lastAngle;
extern double newAngle;
	
	// Variablen für Kanalverarbeitung
extern bool channelA;
extern bool channelB;
extern int lastPhase;
extern int currentPhase;
extern int phaseCounter;

extern int direction; 

/**
 * @brief setzt die Kanäle, Winkelwerte und die Ausgabe auf dem ITSBoard zurück
 * 
 */
void reset();


#endif