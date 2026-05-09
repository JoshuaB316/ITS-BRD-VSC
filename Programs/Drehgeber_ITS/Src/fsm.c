/**
  * @file fsm.c
  * @author Franz Korf, HAW Hamburg 
  * @date October 2016
  * @brief Implementation of finite state machine module. 
  */
  
#include "fsm.h"
#include <stdlib.h>
#include "timecalc.h"

/*
 * Dieses Modul realisiert die FSM, der Zustand nur die aktuelle Phase ist. Drehrichtung und 
 * Fehler sind in separaten Variablen gespeichert.
 */
 
typedef enum {Unknown, Forward, Backword} RotationType;

static RotationType rotation = Unknown;
static PhaseType curPhase; // wird von initFSM initialisiert
static uint32_t tsLastPhaseChange = 0;
static long int phaseCount = 0;
static bool err = false;

long int getPhaseCount(uint32_t *ts){
   if (ts != NULL){
      *ts = tsLastPhaseChange;
   }
   return phaseCount;
}

void resetFSM(void){
   rotation = Unknown;
   phaseCount = 0;
   err = false;
   tsLastPhaseChange = currentTimeStamp();
}

void initFSM(PhaseType phase){
   resetFSM();
   curPhase = phase;
}

bool inErrorState(void){
   return err;
}

bool forwardRotation(void) {
	 return Forward == rotation; 
}

bool backwardRotation(void) {
	 return Backword == rotation; 
}

void changeState(PhaseType phase, uint32_t ts){
   err = err || ((curPhase + 2) % 4 == phase); 
   if (err){
      rotation = Unknown;
      phaseCount = 0;
      return;
   }
   if (curPhase != phase){
      rotation = ((curPhase + 1) % 4 == phase) ? Forward : Backword;         
      phaseCount = phaseCount + ((Forward == rotation) ? 1 : -1);
      curPhase = phase;
      tsLastPhaseChange = ts;
   }
} 
 
// EOF
