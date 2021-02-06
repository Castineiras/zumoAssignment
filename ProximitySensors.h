// Header file containing declarations for "ProximitySensors.cpp".

#pragma once
#include <Zumo32U4.h>
#include <Zumo32U4ProximitySensors.h>

// Must define in main sketch.
extern Zumo32U4ProximitySensors proxSensors;

// Constant Values
const uint16_t levels[] = { 4, 15, 32, 55, 85, 120 };

// Function Declarations
void proximitySensorSetup();
bool readProximitySensors();
