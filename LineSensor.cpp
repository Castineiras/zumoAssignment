#include "LineSensor.h"

void calibrateSensors()
{
  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

// Checks to see if the zumo is at a corner, by seeing if it has a wall directly in front of it. Checks if a line is detected under the centre 3 sensors.
// The outer 2 of these 3 sensors check for a lower value in case the Zumo arrives at the corner at an odd angle.
bool isAtCorner()
{
  return (lineSensorValues[1] > sensorThreshold / 2 && lineSensorValues[2] > sensorThreshold && lineSensorValues[3] > sensorThreshold / 2);
}
