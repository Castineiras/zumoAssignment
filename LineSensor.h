#pragma once
#include <Zumo32U4.h>

// Must be defined in main sketch
extern Zumo32U4Motors motors;
extern Zumo32U4LineSensors lineSensors;
extern int lineSensorValues[numSensors];

// Constant Declarations
const int numSensors = 5;
const int sensorThreshold = 500;

// Function Declarations
void calibrateSensors();
bool isAtCorner();
