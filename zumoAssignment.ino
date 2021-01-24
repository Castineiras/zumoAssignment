#include <Zumo32U4.h>

Zumo32U4Motors motors;

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  motors.setSpeeds(0, 0);
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
        motors.setSpeeds(50, 50);
        break;
        
      case 'b':
        break;
        
      case 'l':
        break;
        
      case 'r':
        break;
        
      case 's':
        motors.setSpeeds(0, 0);
        break;

      default:
        break;
    }
  }
}
