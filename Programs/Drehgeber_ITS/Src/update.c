/**
  * @file update.c
  * @author Franz Korf, HAW Hamburg 
  * @date October 2016
  * @brief Implementation of finite state machine module. 
  */
  
#include "update.h"
#include "fsm.h"
#include "timecalc.h"
#include "output.h"
#include <stm32f4xx_hal.h>

static double angle = 0;         // Einheit: Grad
static double angularSpeed = 0;  // Einheit: Grad / s

/* Fuer eine genaue Berechnung der Winkelgeschwindigkeit werden zwei
 * Zeitintervalle benötigt
 * - Das Zeitintervall, nachdem die Daten aktualisiert werden
 * - Das Zeitintervall zwischen den beiden letzten Phasewechseln
 */ 
static uint32_t tsStartUpdateInterval = 0;  // Start des Update Intervalls
// Zur Berechnung der Winkelgeschwindigkeit
static uint32_t tsOfLastPC = 0;             // Zeitstempel des Starts des Intervalls Winkelberechnung
static long int lastPC = 0;                 // Wert des Phasenzaehlers zum Zeitstempel tsOfLastPC

double getAngle(void){
   return angle;
}

double getAngularSpeed(void){
   return angularSpeed;
}

static void updateAngle(void){
   // 1 tick = 0.3°
	angle = (double) getPhaseCount(NULL) * (double) 0.3;  
}

static void updateAngularSpeed(long int pc1, long int pc2, double interval){
   // Berechnung der Winkelgeschwindigkeit in °/s
   // 1 Phasenwechsel = 0.3°
   angularSpeed = (double) (pc2 - pc1) * (double) 0.3;
   angularSpeed = angularSpeed / interval;
}

#define UPDATE_INTERVAL_IN_S   ((double)0.25)

void initUpdate(void){
   angle = 0;
   angularSpeed = 0;
   tsStartUpdateInterval = currentTimeStamp();   
   lastPC = getPhaseCount(&tsOfLastPC);   
}

void updateUpdate(void){
   // Dieser Berechnung berücksichtig nicht den Fall, dass waehrend des Zeitintervalls
   // die Drehrichtung wechselt. Aufgrund der Groesse des Zeitintervalls ist dies o.k.
	
   // Wichtig ist, dass das Zeitintervall zur Messung der Winkelgeschwindigkeit von Phasenwechsel
   // zu Phasenwechsel geht.
   // Daher warte die Funktion bis zu 2 * UPDATE_INTERVAL_IN_US auf einen Phasewechsel,
   // wenn im Zeitintervall UPDATE_INTERVAL_IN_US mindestens ein Phasenwechsel vorlag.
   
   
   // Erkennung eines Phasewechsel durch Vergleich mit dem aktuellen PhaseCount
      
   uint32_t actTs;
   long int curPC = getPhaseCount(&actTs);
   // Test, ob das Zeitfenster eine Messung vergangen ist. Ggf verlängern, bis Phasenwechsel vorliegt
   double timeInterval  = timerDiffToSec(tsStartUpdateInterval, currentTimeStamp());
   
	if ((UPDATE_INTERVAL_IN_S < timeInterval) && ((curPC != lastPC) || (2*UPDATE_INTERVAL_IN_S < timeInterval)) ){
		 // aktuelle Winkel und Winkelgeschwindigkeit und Intervall für Zeitmessung
       tsStartUpdateInterval = currentTimeStamp();
       updateAngle();    
       updateAngularSpeed(lastPC, curPC, timerDiffToSec(tsOfLastPC, actTs));
       tsOfLastPC = actTs;
       lastPC = curPC;
   }
}

// EOF
