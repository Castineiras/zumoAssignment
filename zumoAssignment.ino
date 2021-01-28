#include <Zumo32U4.h>
#include "TurnSensor.h"

const int numSensors = 5;

Zumo32U4Motors motors;
Zumo32U4IMU imu;
Zumo32U4LineSensors lineSensors;

int moveSpeed = 100;
int turnSpeed = 85;
int lastError = 0;
int lineSensorValues[numSensors];
bool isRunning = false;

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

void setup() 
{
  Serial1.begin(9600);
  motors.setSpeeds(0, 0);
  turnSensorSetup();
  lineSensors.initFiveSensors();
  calibrateSensors();
}

void loop() 
{
  int position;
  int error;
  
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
        if (isRunning)
        {
          isRunning = false;
          motors.setSpeeds(0, 0);
        }
        else
        {
          isRunning = true;
        }
        break;

      default:
        break;
    }
  }
  else if (isRunning)
  {
    position = lineSensors.readLine(lineSensorValues, true, true);
    error = position - 2000;
    int speedDifference = error / 4 + 6 * (error - lastError);
    lastError = error;

    int leftSpeed = moveSpeed + speedDifference;
    int rightSpeed = moveSpeed - speedDifference;

    leftSpeed = constrain(leftSpeed, 0, moveSpeed);
    rightSpeed = constrain(rightSpeed, 0, moveSpeed);

    motors.setSpeeds(leftSpeed, rightSpeed);
  }
}
