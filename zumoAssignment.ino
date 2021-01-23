#include <Zumo32U4.h>

void setup() 
{
  
}

void loop() 
{
  if (Serial.available() > 0)
  {
    String command = Serial.readString();
    
    switch (command)
    {
      case "forward":
        break;
        
      case "back":
        break;
        
      case "left":
        break;
        
      case "right":
        break;
        
      case "stop":
        break;

      default:
        break;
    }
  }
}
