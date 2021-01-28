// Provides functions for calibrating Zumo's onboard gyro, and using it to measure turns about the z-axis.

#include <Wire.h>
#include "TurnSensor.h"

uint32_t turnAngle = 0;         // Value of 0x20000000 represents a 45 degree turn, therefore uint32_t can represent 0 to 360 degrees.
int16_t turnRate;               // Current angular rate of the gyro, in units of 0.07 degrees per second.
int16_t gyroOffset;             // Average reading from gyro's z-axis during calibration.
uint16_t gyroLastUpdate = 0;    // Used to keep track of time passed between gyro readings.

// Should be called in setup() located in main sketch.
void turnSensorSetup()
{
  Wire.begin();
  imu.init();
  imu.enableDefault();
  imu.configureForTurnSensing();

  // Turn on LED to show setup is being run.
  ledYellow(1);

  // Delay slightly to give the user time after turning on the robot.
  delay(500);

  // Main calibration for the gyro.
  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++)
  {
    // Wait for data first before reading it.
    while(!imu.gyroDataReady())
    {
      
    }
    imu.readGyro();

    // Add the z-axis value to the total.
    total += imu.g.z;
  }

  // Turn off LED to show setup is complete
  ledYellow(0);
  gyroOffset = total / 1024;

  // Reset the value once calibrated.
  turnSensorReset();
}

// To be called before each turn in order to reset the turn angle.
void turnSensorReset()
{
  gyroLastUpdate = micros();
  turnAngle = 0;
}

// Should be called in order to read the gyro and update the angle accordingly.
void turnSensorUpdate()
{
  // Get values from the gyro.
  imu.readGyro();
  turnRate = imu.g.z - gyroOffset;

  // Get the time passed since the gyro's last update.
  uint16_t m = micros();
  uint16_t dt = m - gyroLastUpdate;
  gyroLastUpdate = m;

  // Use dt * turnRate to get an estimation of the amount turned since last update.
  // (angular change = angular velocity * time)
  int32_t d = (int32_t)turnRate * dt;

  // The units of d are gyro digits times microseconds.  We need
  // to convert those to the units of turnAngle, where 2^29 units
  // represents 45 degrees.  The conversion from gyro digits to
  // degrees per second (dps) is determined by the sensitivity of
  // the gyro: 0.07 degrees per second per digit.
  //
  // (0.07 dps/digit) * (1/1000000 s/us) * (2^29/45 unit/degree)
  // = 14680064/17578125 unit/(digit*us)
  turnAngle += (int64_t)d * 14680064 / 17578125;
}
