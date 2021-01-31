#pragma once
#include <Zumo32U4.h>

// Constant Declarations
const int32_t turnAngle45 = 0x20000000; //Represents 45 degreee turn
const int32_t turnAngle90 = turnAngle45 * 2; //Represents 90 degreee turn
const int32_t turnAngle1 = (turnAngle45 + 22) / 45; //Represents 1 degreee turn

// Function Declarations
void turnSensorSetup();
void turnSensorReset();
void turnSensorUpdate();
extern uint32_t turnAngle;
extern int16_t turnRate;

// Must define these in sketch
extern Zumo32U4IMU imu;
