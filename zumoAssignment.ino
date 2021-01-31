#include <Zumo32U4.h>
#include "TurnSensor.h"
#include "LineSensor.h"

Zumo32U4Motors motors;
Zumo32U4IMU imu;
Zumo32U4LineSensors lineSensors;

int moveSpeed = 100;
int turnSpeed = 85;
int lastError = 0;
int lineSensorValues[numSensors];
bool isRunning = false;
bool isAutonomous = true;

//----------------------------------
//--------------Setup---------------
//----------------------------------
void setup() 
{
  // Ran once, calibrates all sensors and opens the serial port.
  Serial1.begin(9600);
  turnSensorSetup();
  lineSensors.initFiveSensors();
  calibrateSensors();
}


//----------------------------------
//------------Main Loop-------------
//----------------------------------
void loop() 
{    
  if (Serial1.available() > 0) // Only execute if something is sent through the serial.
  {
    String commandString = Serial1.readString();
    char command = commandString[0];

    // Check current control scheme
    if (isAutonomous)
    {
      autonomousControl(command); // Autonomous - Main functionality, used for moving through the maze and searching rooms etc.
    }
    else
    {
      manualControl(command); // Manual - Direct manual controls, only really used for Task 1.
    }
  }
  else if (isRunning) // isRunning should be true when moving forward autonomously. Keeps the Zumo from travelling outside the boundaries of the maze.
  {
    int position = lineSensors.readLine(lineSensorValues, true, true);
    int error = position - 2000;
    int speedDifference = error / 4 + 6 * (error - lastError);
    lastError = error;

    int leftSpeed = moveSpeed + speedDifference;
    int rightSpeed = moveSpeed - speedDifference;

    leftSpeed = constrain(leftSpeed, 0, moveSpeed);
    rightSpeed = constrain(rightSpeed, 0, moveSpeed);

    motors.setSpeeds(leftSpeed, rightSpeed);
  }
}


//----------------------------------
//--------Control Functions---------
//----------------------------------
void manualControl(char command)
{
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

void autonomousControl(char command)
{
  switch (command)
  {
    // Start autonomous forward movement.
    case 'f':
      isRunning = true;
      break;

    // Turn the robot to the left 90 degrees.
    case 'l':
      turnSensorReset();
      motors.setSpeeds(-turnSpeed, turnSpeed);
      while((int32_t)turnAngle < turnAngle90)
      {
        turnSensorUpdate();
      }
      isRunning = false;
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
      isRunning = false;
      motors.setSpeeds(0, 0);
      break;

    // Stop all current movement of the robot.
    case 's':
      isRunning = false;
      motors.setSpeeds(0, 0);
      break;

    // Default case, should never be executed.
    default:
      break;
  }
}
