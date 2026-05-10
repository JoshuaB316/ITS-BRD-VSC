/**
 * @file    rechnen.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date    Mai 2026
 */

#include "calculate.h"
#include <stdint.h>

#define PHASE_SHIFTS_PER_ROTATION 1200.0

double calculateDegree(uint32_t steps) {

  double stepsPerRotation = PHASE_SHIFTS_PER_ROTATION;
  double rotationAngle = (steps / stepsPerRotation) * 360.0;

  return rotationAngle;
}

double calculateAnglespeed(double lastAngle, double currentAngle, uint32_t oldTime, uint32_t currentTime) {

  double timeInSec = (currentTime - oldTime) / 90000000.0; // Millisekunden in Sekunden umrechnen unter be
  double angle = currentAngle - lastAngle;
  double anglespeedPerSec = angle / timeInSec;

  return anglespeedPerSec;
}