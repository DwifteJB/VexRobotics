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
motor claw = motor(PORT8, false);
sonar dist = sonar(PORT3);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;




#pragma endregion VEXcode Generated Robot Configuration
//----------------------------------------------------------------------------
//                                                                            
//    Module:       code.cpp                                                  
//    Author:       Owen Exon and Robbie Elliott                                                  
//    Created:      22/03/2022                                                    
//    Description:  Baller bot                                             
//                                                                            
//----------------------------------------------------------------------------

// Include the IQ Library
#include "iq_cpp.h"

// Global Variables
bool bypass_autoclamp = false;
bool STOPMOVINGPLEASE = false;
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
  Brain.Screen.print("Baller: v1.0");
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
  Brain.Screen.print("byp: %d", (bool)bypass_autoclamp);
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Claw Pos: %d", (char)claw.position(degrees));
}

void checkVisual() {
  basicScreen(false);
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Object found: %d", (bool)dist.foundObject());
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Distance: %dmm", (int)dist.distance(mm));
}
void autoGrab() {
  if (dist.distance(mm) < 110 && bypass_autoclamp == false) {
    checkVisual();
    // I found the object within 110mm of the claw. What should I do?
    // What should I add next? :)
  }
}
void autoClampToggle() {
  if(bypass_autoclamp == true) {
    bypass_autoclamp = false;
  } else {
    bypass_autoclamp = true; // This is so simple, thank you previous nodejs knowledge!
  }
}
void clawMovement() {
  // Clamps the Motor
  // WE NEED MAX TO MAKE A CLAMP.
  // if (claw.position(degrees) < -70){
  //   claw.position(turns);
  //   claw.spin(reverse);
  //   //claw.spinToPosition(-60,degrees,true);
  //   claw.spinToPosition(0,degrees,true);
  //   return claw.stop();
  // }
  // else {
  //   if(claw.isSpinning()) {return;}
  //   claw.spin(forward);
  //   claw.setVelocity(Controller.AxisD.position(percent),percent);
  // }
  claw.spin(forward);
  claw.setVelocity(Controller.AxisD.position(percent),percent);
}
int main() {
  // Initialize the robot
  init();
  // Allows claw movement on the D Axis
  Controller.AxisD.changed(clawMovement);
  // If the distance is changed, start autoGrab()
  dist.changed(autoGrab);
  // Buttons
  // Debugging Menu
  Brain.buttonUp.pressed(checkClaw);
  Brain.buttonDown.pressed(checkVisual);
  // Turning off/on Autoclamp
  Controller.ButtonEUp.pressed(autoClampToggle);
  checkClaw();

}
// ROBOT ENDS HERE
