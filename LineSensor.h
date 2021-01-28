#pragma once
#include <Zumo32U4.h>

extern Zumo32U4Motors motors;
extern Zumo32U4LineSensors lineSensors;

const int numSensors = 5;
const int sensorThreshold = 500;
extern int lineSensorValues[numSensors];

void calibrateSensors();
bool isAtCorner();
