Programming 'Things' - Zumo Assignment

Required Libraries
Libraries can be installed for the Arduino IDE by going to “Tools > Manage Libraries” or by using “Ctrl + Shift + I”. The ones used in this project are listed below;
* Zumo32U4 by Polulu – Version 1.2.0 – For Zumo functionality.
* ArxContainer by hideakitai – Version 0.3.10 – For container classes such as vector.

Task 1 – Manual Control
Manual control of the Zumo was very simple to complete, it works just by setting the speed of the motors to the default movement speed when the forward command is received, and the negative of the value when the backward command is received. I found a Github repository to help deal with turning corners, the source for which can be found in the code sources section near the bottom of this document. It works by using the on-board gyro to measure the distance turned, and stopping when reaching x degrees. Instructions for this task are listed below;
1. Firstly, ensure the Zumo is in manual control mode, by using the “Switch Controls” button. (By default it is set to autonomous)
2. Then simply use each of the 5 buttons listed to move and turn in the respective directions.
3. Press the “Stop” button to halt all movement.

Task 2 – Automatic Movement
Once automatic movement was needed I opted to use two separate control schemes which could be switched at will, one for the manual control in the previous task, and one for autonomous control needed for the rest of the assignment. In order to keep the Zumo within the confines of the maze I tweaked one of the example projects given with the Zumo, the “LineFollower”, and rather than follow a black line, it now follows a thick white line which is actually the corridor. Any movement too far to the left or right will be corrected as the Zumo will try and move away from the black edges in order to follow the corridor better. The Zumo also stops at the end of the corridor, by checking the values of the middle three line sensors, in order to determine if a black line is directly in front of it. Instructions for this task are listed below;
1. Begin by placing the Zumo at the start of the maze and turning it on. Wait a few seconds for it to complete its sensor calibration.
2. When in autonomous control mode, press the “Start/Stop” button on the right hand side of the GUI, this will begin automatic movement.
3. Once the Zumo reaches the end of the corridor, it will automatically stop.

Task 3 – Turning Corners
Extending on from task 2, the Zumo now also sends a message via the xBee stating that it is at a corner, prompting the user to select a direction to turn. This message is displayed in a text area at the bottom of the GUI that shows all messages received through the serial port. As I had already dealt with turning 90 degrees in task 1, I could just reuse that functionality for this task. After the turn has been completed the user just needs to press the start button again in order to continue autonomous movement through the corridor. Instructions for this task are listed below;
1. After using the automatic movement from task 2, the Zumo will come to a stop at the end of the corridor.
2. Once stopped, press either the “Turn Right” or “Turn Left” button, depending on which way you need the Zumo to turn.
3. Once the turn is complete, press the “Start/Stop” button again in order to have the Zumo resume movement.

Task 4 – Automatic Turning
Due to the way I had completed the previous tasks, all that was needed was a small adjustment, which was to change a Boolean value after each turn the Zumo makes. Autonomous movement is linked to the “isRunning” variable, so as long as that was set to true after it completes the 90 degree turn, the Zumo should carry on automatically. Instructions for this task are the same as task 3, it just requires using a branch of the code from task 4 or later. The final step can also be ignored as the Zumo will continue on its own.

Task 5 – Room Searching
Room searching is handled by two controls on the GUI. Each one is functionally similar, however they each signal to the Zumo what direction the room is in relation to itself. Once the signal has been sent, the Zumo then turns 90 degrees in the specified direction and moves forward to enter the room. It does a sweep from left to right, checking all three proximity sensors every 45 degrees to check for any objects within the room. Once the search is complete, it turns to leave the room, relays through the xBee what the results were of the search, and then leaves and turns to face the same direction it was before the search. Instructions for this task are listed below;
1. Whilst the Zumo is moving autonomously through the corridor, press the “Start/Stop” button as it comes to the entrance of a room.
2. Once the Zumo has stopped, press the “Room Left” or “Room Right” button, depending on which direction the room is relative to the Zumo.
3. Wait for the Zumo to complete the search procedure, and once it has returned to the corridor, press the “Start/Stop” button again to resume movement.

Task 6 – The T-Junction
Once at the T-Junction the user can just turn the Zumo down either side of it. Once it reaches the end, pressing the ‘End of T-Junction’ button will signal to the Zumo to turn around and move to check the other end of the corridor. At this point it will begin ignoring all commands sent to it, and will only resume control after sending either a ‘Turn Right’ or ‘Turn Left’ command, to signal that it has passed the main corridor and is now on the other side of the T-Junction. Instructions for this task are listed below;
1. Once the Zumo has come to a stop at the T-Junction, press the “Turn Right” or “Turn Left” button. The direction doesn’t matter as it will come back to search the other way.
2. Once the Zumo reaches the end of the corridor, press the “End of T-Junction” button. This will turn the Zumo around, start it moving, and ignore all incoming commands.
3. Control will be handed back to the user once the Zumo receives the next turn command, regardless of direction. This signals that it has passed the main corridor, and is in the other end of the T-Junction now.
4. Continue controlling the Zumo as normal from this point.

Task 7 – Return Journey
The return journey was where I had the most difficulty, and is by far the least complete out of all the tasks. As long as the Zumo doesn’t turn into any rooms and just follows the corridors, pressing the “Return Home” button while stopped will spin the Zumo around and make it retrace its steps back to the starting point. It does this by getting the total count on both the encoders whenever it stops, and uses that to calculate the distance of the last path travelled. It also uses the last turn direction, and reverses that on the return journey in order to make the correct turns. Unfortunately stopping to turn into any room will break this functionality. Instructions for this task are listed below;
1. As searching rooms is not implemented when doing a return journey, only move through the main corridors until it has come to a stopping point.
2. Press the “Return Home” button and the Zumo will track its way back to its starting position and stop.

Code Sources
TurnSensor.h & cpp - https://github.com/pvcraven/zumo_32u4_examples/tree/master/TurnExample

lineSensor.h & cpp - https://github.com/pololu/zumo-32u4-arduino-library/blob/master/examples/LineFollower/LineFollower.ino

autoMove() - https://github.com/pololu/zumo-32u4-arduino-library/blob/master/examples/LineFollower/LineFollower.ino

Control Reference
All control for the Zumo will be done via the buttons visible on the GUI; however they will be detailed here for reference as well. 

Manual Controls;
* Forward – Begins moving the Zumo forward at default speed.
* Turn Left – Turns the Zumo to the left 90 degrees.
* Turn Right – Turns the Zumo to the right 90 degrees.
* Back – Begins moving the Zumo forward at default speed.
* Stop – Stops all movement for the Zumo.
* Switch Controls – Swaps to the autonomous control scheme.

Automatic Controls;
* Start/Stop – Alternates between automatic forward movement (avoiding the edges of the maze) and the stopped state for the Zumo.
* Turn Left – Turns the Zumo to the left 90 degrees.
* Turn Right – Turns the Zumo to the right 90 degrees.
* Room Left – Signals to the Zumo that there is a Room on its left, it will then turn into this and perform a sweep to check if it is empty or not.
* Room Right – Same as the above, except this time it signals the room is located on its right.
* End of T-Junction – Signals to the Zumo that it is at the end of the T-Junction. It then turns around to go check the other end. It will ignore instructions until after the next ‘Turn Right’ or ‘Turn Left’ input; these must be sent to let the Zumo know it has passed the corridor.
* Return Home – The Zumo tracks back its path to return to its start point, turning automatically.
* Switch Controls – Swaps to the manual control scheme.
