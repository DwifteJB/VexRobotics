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
void checkVisual() {
  basicScreen(false);
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Object found: %d", (bool)dist.foundObject());
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Distance: %dmm", (int)dist.distance(mm));
}
void clawMovement() {
  // clamp system
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
  // Init the bot
  init();
  // Allows claw movement on the D Axis
  Controller.AxisD.changed(clawMovement);
  // checking stuff
  Brain.buttonUp.pressed(checkClaw);
  Brain.buttonDown.pressed(checkVisual);
}

// ROBOT ENDS HERE