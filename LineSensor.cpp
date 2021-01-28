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

bool isAtCorner()
{
  return (lineSensorValues[1] > sensorThreshold / 2 && lineSensorValues[2] > sensorThreshold && lineSensorValues[3] > sensorThreshold / 2)
}
