#include <ArxContainer.h>
#include <Zumo32U4.h>
#include <Zumo32U4Encoders.h>
#include "TurnSensor.h"
#include "LineSensor.h"
#include "ProximitySensors.h"

Zumo32U4Motors motors;
Zumo32U4IMU imu;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Encoders encoders;

int moveSpeed = 100;
int turnSpeed = 85;
int lastError = 0;
int lineSensorValues[numSensors];
int currentRoomNumber = 0;
char lastTurnDirection;
bool isRunning = false;
bool isAutonomous = true;
bool isIgnoringCommands = false;

struct Room
{
  int number;
  bool isClear;
};

struct Path
{
  int distance;
  char endTurnDirection;
};

arx::vector<Room> rooms;
arx::vector<Path> paths;

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
  encoders.init();
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

    // First block should only be executed when checking the other side of the T-Junction.
    if (isIgnoringCommands)
    {
      // Ignore commands until the zumo is asked to turn back down the main corridor.      
      if(command == 'l' || command == 'r')
      {
        isIgnoringCommands = false;
        Serial1.write("Control Resumed \n");
      }
      else
      {
        Serial1.write("Ignoring Commands \n");
      } 
    }
    // Check current control scheme     
    else if (isAutonomous)
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
    autoMove();
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
      lastTurnDirection = 'l';
      logPath(); // Logs path after manual turn as these are only done when at a corner.
      break;

    // Turn the robot to the right 90 degrees.
    case 'r':
      Serial1.write("Turning Right \n");
      turnRight90();
      Serial1.write("Moving \n");
      isRunning = true;
      lastTurnDirection = 'r';
      logPath(); // Logs path after manual turn as these are only done when at a corner.
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

    // Turn the robot 180 degrees and search the other side of the T-Junction, ignoring commands until it has passed the main corridor turning.
    case 'b':
      turnRight90();
      turnRight90();
      isIgnoringCommands = true;
      isRunning = true;
      break;

    case 'h':
      returnHome();
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
    logPath();
  }
}

// Moves the zumo forward at default speed for x milliseconds.
void moveForward(int x)
{
  motors.setSpeeds(moveSpeed, moveSpeed);
  delay(x);
  motors.setSpeeds(0, 0);
}

// Automatically moves the zumo forward, whilst keeping itself within the confines of the maze.
void autoMove()
{
    // This works by effectively following the white area inside the maze, in order to avoid the boundaries.
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


//----------------------------------
//-------Searching Functions--------
//----------------------------------
// Executes a 90 degree left turn and returns true if anything is detected by the proximity sensors.
// Checks the proximity sensors every 45 degrees.
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
// Checks the proximity sensors every 45 degrees.
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
  currentRoomNumber++; // Increase the number of the room upon each search (starts at 0).
  Serial1.print("Searching Room " + String(currentRoomNumber) + "\n");

  // Move into the room.
  moveForward(500);

  // Turn to the left 90 degrees and see if anything is detected by the proximity sensors.
  objectDetected = turnLeftAndSearch();

  // Turn back to the right 180 degrees, and see if anything is detected by the proximity sensors.
  objectDetected = turnRightAndSearch();
  objectDetected = turnRightAndSearch();

  // Relay through the serial if an object was detected in the current room.
  if (objectDetected == true)
  {
    Serial1.print("Object Detected in Room " + String(currentRoomNumber) + "\n");
  }
  else
  {
    Serial1.print("Room " + String(currentRoomNumber) + " clear \n");
  }

  logRoom(objectDetected);
  
  // Turn and exit the room.
  turnRight90();
  moveForward(500);
}

// Creates a new Room structure and adds it to the list of rooms, based on the last room searched.
void logRoom(bool c)
{
  Room r{};
  r.number = currentRoomNumber;
  r.isClear = c;

  rooms.push_back(r);
}


//----------------------------------
//--------Pathing Functions---------
//----------------------------------
// Set of functions related to mapping the path for the zumo's return journey.

// Creates a new Path structure and adds it to the list of paths, based on the last path travelled through the maze.
void logPath()
{
  Path p = Path();
  p.distance = encoders.getCountsAndResetLeft() + encoders.getCountsAndResetRight();
  p.endTurnDirection = lastTurnDirection;
  paths.push_back(p);
}

// Checks whether the zumo has fully travelled the distance for the current path on the return journey.
bool compareDistances(int pathNo)
{
  int currentDistance = encoders.getCountsLeft() + encoders.getCountsRight();
  int pathDistance = paths[pathNo].distance;

  // Gives a small amount of leniency to account for the zumo not travelling perfectly straight each time.
  if (currentDistance >= pathDistance * 0.99)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Takes the zumo back to the starting point of the maze automatically.
void returnHome()
{
  // Says whether or not the zumo has travelled the same amount of distance as the current path length.
  bool matchedDistance = false;
  
  // Spin around 180 degrees before moving.
  turnRight90();
  turnRight90();
  
  // For each path in the vector, starting from the last.
  for (int i = paths.size() - 1; i >= 0; i--)
  {
    while(matchedDistance == false)
    {
      autoMove();
      matchedDistance = compareDistances(i);
    }

    // If the zumo isn't on the last path of the return journey.
    if (i != 0)
    {
      // Turn the opposite direction that the zumo turned when initially travelling through that path of the maze.
      if (paths[i - 1].endTurnDirection == 'r')
      {
        turnLeft90();
      }
      else
      {
        turnRight90();
      }
    }

    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
    matchedDistance = false;
  }

  motors.setSpeeds(0, 0);
  isRunning = false;
}
