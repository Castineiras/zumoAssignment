#include <Zumo32U4.h>
#include "TurnSensor.h"

Zumo32U4Motors motors;
Zumo32U4IMU imu;

int moveSpeed = 50;   // Starting speed for general movement.
int turnSpeed = 85;   // Motor speed used when turning.

void setup() 
{
  // Use Serial1 for communication via xBee module.
  Serial1.begin(9600);
  turnSensorSetup();
}

void loop() 
{
  // Wait for input from the Serial monitor for 
  if (Serial1.available() > 0)
  {
    // Get first letter of command for use in switch statement i.e. F for forward, B for backward etc.
    String commandString = Serial1.readString();
    char command = commandString[0];
    
    switch (command)
    {
      // Start manual forward movement.
      case 'f':
        motors.setSpeeds(moveSpeed, moveSpeed);
        break;

      // Start manual backward movement.
      case 'b':
        motors.setSpeeds(-moveSpeed, -moveSpeed);
        break;

      // Turn the robot to the left 90 degrees.
      case 'l':
        turnSensorReset();
        motors.setSpeeds(-turnSpeed, turnSpeed);
        while((int32_t)turnAngle < turnAngle90)
        {
          turnSensorUpdate();
        }
        motors.setSpeeds(0, 0);
        break;

      // Turn the robot to the right 90 degrees.
      case 'r':
        turnSensorReset();
        motors.setSpeeds(turnSpeed, -turnSpeed);
        while((int32_t)turnAngle > -turnAngle90)
        {
          turnSensorUpdate();
        }
        motors.setSpeeds(0, 0);
        break;

      // Stop all current movement of the robot.
      case 's':
        motors.setSpeeds(0, 0);
        break;

      // Default case, should never be executed.
      default:
        break;
    }
  }
}
