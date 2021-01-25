#include <Zumo32U4.h>
#include "TurnSensor.h"

Zumo32U4Motors motors;
Zumo32U4IMU imu;

int moveSpeed = 50;
int turnSpeed = 85;

void setup() 
{
  Serial1.begin(9600);
  motors.setSpeeds(0, 0);
  turnSensorSetup();
}

void loop() 
{
  if (Serial1.available() > 0)
  {
    String commandString = Serial1.readString();
    char command = commandString[0];
    
    switch (command)
    {
      case 'f':
        motors.setSpeeds(moveSpeed, moveSpeed);
        break;
        
      case 'b':
        motors.setSpeeds(-moveSpeed, -moveSpeed);
        break;
        
      case 'l':
        turnSensorReset();
        motors.setSpeeds(-turnSpeed, turnSpeed);
        while((int32_t)turnAngle < turnAngle90)
        {
          turnSensorUpdate();
        }
        motors.setSpeeds(0, 0);
        break;
        
      case 'r':
        turnSensorReset();
        motors.setSpeeds(turnSpeed, -turnSpeed);
        while((int32_t)turnAngle > -turnAngle90)
        {
          turnSensorUpdate();
        }
        motors.setSpeeds(0, 0);
        break;
        
      case 's':
        motors.setSpeeds(0, 0);
        break;

      default:
        break;
    }
  }
}
