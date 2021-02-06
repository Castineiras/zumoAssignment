// Provides functions for using the Zumo's onboard proximity sensors to detect objects in the 'Rooms' of the maze.

#include "ProximitySensors.h"

// Initial setup for proximity sensors. Set brightness levels in order to lower the default range of the sensors.
void proximitySensorSetup()
{
  proxSensors.initThreeSensors();
  proxSensors.setBrightnessLevels(levels, 4);
}

// Read the sensors and see if anything is detected within range.
bool readProximitySensors()
{
  proxSensors.read();
  if (proxSensors.countsFrontWithLeftLeds() > 0 || proxSensors.countsFrontWithRightLeds() > 0)
  {
    return true;
  }
  else if (proxSensors.countsLeftWithLeftLeds() > 0 || proxSensors.countsLeftWithRightLeds() > 0)
  {
    return true;
  }
  else if (proxSensors.countsRightWithLeftLeds() > 0 || proxSensors.countsRightWithRightLeds() > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
