#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START IQ MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END IQ MACROS


// Robot configuration code.
controller Controller = controller();
motor LeftDriveSmart = motor(PORT6, 1, false);
motor RightDriveSmart = motor(PORT12, 1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 200, 165, 130, mm, 1);
motor claw = motor(PORT8, false);
sonar dist = sonar(PORT3);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainNeedsToBeStopped_Controller = true;

// define a task that will handle monitoring inputs from Controller
int rc_auto_loop_function_Controller() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = AxisA + AxisB
      // right = AxisA - AxisB
      int drivetrainLeftSideSpeed = Controller.AxisA.position() + Controller.AxisB.position();
      int drivetrainRightSideSpeed = Controller.AxisA.position() - Controller.AxisB.position();
      
      // check if the values are inside of the deadband range
      if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5) {
        // check if the motors have already been stopped
        if (DrivetrainNeedsToBeStopped_Controller) {
          // stop the drive motors
          LeftDriveSmart.stop();
          RightDriveSmart.stop();
          // tell the code that the motors have been stopped
          DrivetrainNeedsToBeStopped_Controller = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the motors next time the input is in the deadband range
        DrivetrainNeedsToBeStopped_Controller = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller(rc_auto_loop_function_Controller);



#pragma endregion VEXcode Generated Robot Configuration

//----------------------------------------------------------------------------
//                                                                            
//    Module:       main.cpp                                                  
//    Author:       Owen Exon and Robbie Elliott                                                  
//    Created:      22/03/2022                                                    
//    Description:  JoshBot V1                                               
//                                                                            
//----------------------------------------------------------------------------

// Include the IQ Library
#include "iq_cpp.h"

// Global Variables

bool bypass_autoclamp = false;
// Allows for easier use of the VEX Library
using namespace vex;
// Functions

//
// EG: basicScreen(boolean);
// Desc: Creates a basic screen
// Vars: boolean, determines if you want to clear the screen or not (not recommended)
//
void basicScreen(bool remove){
 //Check if you want to clear screen
  if (remove == false) {
    Brain.Screen.clearScreen();
  }
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("OWEN BOT: v1.0");
  Brain.Screen.newLine();
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Battery: %d%%", Brain.Battery.capacity());
}

// ROBOT STARTS HERE

void init() {
  // Startup script
  basicScreen(false);
}
void checkClaw() {
  basicScreen(false);
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Spinning: %d", (bool)claw.isSpinning());
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Claw Velocity: %d", (char)claw.velocity(percent));
}
void autoGrab() {
  

}
void checkVisual() {
  basicScreen(false);
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Object found: %d", (bool)dist.foundObject());
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Distance: %dmm", (int)dist.distance(mm));
}
void clawMovement() {
  // Clamps the Motor
  if (claw.position(degrees) < -230){
    claw.spin(reverse);
    claw.setVelocity(20,percent);
    wait(1,seconds);
    claw.stop();
    return;
  }
  else if (claw.position(degrees) > 1){
    claw.spin(forward);
    claw.setVelocity(20,percent);
    wait(1,seconds);
    claw.stop();
    return;
  }
  else {
    claw.spin(forward);
    claw.setVelocity(Controller.AxisD.position(percent),percent);
  }
  checkClaw();
}
int main() {
  // Initialize the robot
  init();
  // Allows claw movement on the D Axis
  Controller.AxisD.changed(clawMovement);
  // Debugging Menu
  Brain.buttonUp.pressed(checkClaw);
  Brain.buttonDown.pressed(checkVisual);
  dist.changed(autoClaw);
}

// ROBOT ENDS HERE