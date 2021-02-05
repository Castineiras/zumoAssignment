#include <Zumo32U4.h>
#include "TurnSensor.h"
#include "LineSensor.h"
#include "ProximitySensors.h"

Zumo32U4Motors motors;
Zumo32U4IMU imu;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;

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
  proximitySensorSetup();
  calibrateSensors();
}


//----------------------------------
//------------Main Loop-------------
//----------------------------------
void loop() 
{ 
  lineSensors.read(lineSensorValues); // Must be called before using lineSensorValues in isAtCorner().
  if (isRunning && isAutonomous && isAtCorner()) // If a wall is detected directly in front of the Zumo, stop all movement and notify the user through the serial port. Ignore if in manual control mode.
  {
    Serial1.write("Corner Detected \n"); // Must have \n at the end, as UI looks for this when receiving messages.
    isRunning = false;
    motors.setSpeeds(0, 0);    
  }
  else if (Serial1.available() > 0) // Only execute if something is sent through the serial.
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
    // Block of code works by effectively following the white area inside the maze, in order to avoid the boundaries.
    // Gets the position of the line to be followed.
    int position = lineSensors.readLine(lineSensorValues, true, true);

    // Error is how far the zumo is from the centre of the line, corresponds to position 2000.
    int error = position - 2000;

    // Gets the speed difference to be used between each motor, which will decide what direction it should turn.
    int speedDifference = error / 4 + 6 * (error - lastError);
    
    lastError = error;

    // Set the speeds of the left and right motors, taking into account the speed difference.
    int leftSpeed = moveSpeed + speedDifference;
    int rightSpeed = moveSpeed - speedDifference;

    // Contrains the motor speeds between 0 and the actual movement speed of the robot normally.
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
      Serial1.write("Turning Left \n");
      turnLeft90();
      break;

    // Turn the robot to the right 90 degrees.
    case 'r':
      Serial1.write("Turning Right \n");
      turnRight90();
      break;

    // Stop all current movement of the robot.
    case 's':
      motors.setSpeeds(0, 0);
      break;

    // Swap control schemes for the zumo.
    case 'x':
      isAutonomous = !isAutonomous;
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
    // Start or stop autonomous forward movement.
    case 's':
      startStop();
      break;

    // Turn the robot to the left 90 degrees.
    case 'l':
      Serial1.write("Turning Left \n");
      turnLeft90();
      Serial1.write("Moving \n");      
      isRunning = true;
      break;

    // Turn the robot to the right 90 degrees.
    case 'r':
      Serial1.write("Turning Right \n");
      turnRight90();
      Serial1.write("Moving \n");
      isRunning = true;
      break;

    // Turn the robot to the left 90 degrees, and then search the room ahead. Turns back the correct direction after leaving the room.
    case 'q':
      turnLeft90();
      searchRoom();
      turnLeft90();
      break;

    // Turn the robot to the right 90 degrees, and then search the room ahead. Turns back the correct direction after leaving the room.
    case 'e':
      turnRight90();
      searchRoom();
      turnRight90();
      break;

    // Swap control schemes for the zumo.
    case 'x':
      isAutonomous = !isAutonomous;
      break;

    // Default case, should never be executed.
    default:
      break;
  }
}


//----------------------------------
//--------Turning Functions---------
//----------------------------------
// Execute a 90 degree left turn.
void turnLeft90()
{
  turnSensorReset();
  motors.setSpeeds(-turnSpeed, turnSpeed);
  while((int32_t)turnAngle < turnAngle90)
  {
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
}

// Execute a 45 degree left turn.
void turnLeft45()
{
  turnSensorReset();
  motors.setSpeeds(-turnSpeed, turnSpeed);
  while((int32_t)turnAngle < turnAngle45)
  {
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
}

// Execute a x degree left turn.
void turnLeft(int x)
{
  for (int i = 0; i < x; i++)
  {
    turnSensorReset();
    motors.setSpeeds(-turnSpeed, turnSpeed);
    while((int32_t)turnAngle < turnAngle1)
    {
      turnSensorUpdate();
    }  
  }
  motors.setSpeeds(0,0);
}

// Execute a 90 degree right turn.
void turnRight90()
{
  turnSensorReset();
  motors.setSpeeds(turnSpeed, -turnSpeed);
  while((int32_t)turnAngle > -turnAngle90)
  {
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
}

// Execute a 45 degree right turn.
void turnRight45()
{
  turnSensorReset();
  motors.setSpeeds(turnSpeed, -turnSpeed);
  while((int32_t)turnAngle > -turnAngle45)
  {
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
}

// Execute a x degree right turn.
void turnRight(int x)
{
  for (int i = 0; i < x; i++)
  {
    turnSensorReset();
    motors.setSpeeds(turnSpeed, -turnSpeed);
    while((int32_t)turnAngle > -turnAngle1)
    {
      turnSensorUpdate();
    }
  }
  motors.setSpeeds(0,0);
}


//----------------------------------
//-----Basic Movement Functions-----
//----------------------------------
// Alternates between start and stopped states for the Zumo.
void startStop()
{
  isRunning = !isRunning;
  if (isRunning)
  {
    Serial1.write("Moving \n");
  }
  else
  {
    Serial1.write("Stopping \n");
    motors.setSpeeds(0, 0);
  }
}

// Moves the zumo forward at default speed for x milliseconds.
void moveForward(int x)
{
  motors.setSpeeds(moveSpeed, moveSpeed);
  delay(x);
  motors.setSpeeds(0, 0);
}


//----------------------------------
//-------Searching Functions--------
//----------------------------------
// Executes a 90 degree left turn and returns true if anything is detected by the proximity sensors.
bool turnLeftAndSearch()
{
  bool objectDetected = false;
  for (int i = 0; i < 2; i++)
  {
    turnLeft45();
    objectDetected = readProximitySensors();
  }
  return objectDetected;
}

// Executes a 90 degree right turn and returns true if anything is detected by the proximity sensors.
bool turnRightAndSearch()
{
  bool objectDetected = false;
  for (int i = 0; i < 2; i++)
  {
    turnRight45();
    objectDetected = readProximitySensors();
  }
  return objectDetected;
}

// Moves into and then subsequently scans the room using the onboard proximity sensors.
void searchRoom()
{
  bool objectDetected = false; // Default to nothing detected when first entering a room;

  // Move into the room.
  moveForward(500);

  // Turn to the left 90 degrees and see if anything is detected by the proximity sensors.
  objectDetected = turnLeftAndSearch();

  // Turn back to the right 180 degrees, and see if anything is detected by the proximity sensors.
  objectDetected = turnRightAndSearch();
  objectDetected = turnRightAndSearch();

  // Relay through the serial that an object was detected in the current room.
  if (objectDetected == true)
  {
    Serial1.write("Object Detected in Room \n");
  }
  else
  {
    Serial1.write("Room clear \n");
  }

  // Turn and exit the room.
  turnRight90();
  moveForward(500);
}
