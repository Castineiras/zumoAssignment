#pragma once
#include <Zumo32U4.h>

// Constant Declarations
const int numSensors = 5;
const int sensorThreshold = 500;

// Must be defined in main sketch
extern Zumo32U4Motors motors;
extern Zumo32U4LineSensors lineSensors;
extern int lineSensorValues[numSensors];

// Function Declarations
void calibrateSensors();
bool isAtCorner();
