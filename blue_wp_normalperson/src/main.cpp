#include "vex.h"
#include <iostream>
#include <string>

using namespace vex;
bool conveyorToggle = false;

int img = 3;
double speed = 56.7; //inches per second

competition Competition;

//user control function
void onevent_Controller1ButtonL1_pressed_0() {
  conveyorToggle = !conveyorToggle;
}
void onevent_Controller1ButtonR2_pressed_0() {
  clamp.spinFor(forward, 90, degrees);
  clamp.setVelocity(100, percent);
}
void onevent_Controller1ButtonR1_pressed_0() {
  clamp.spinFor(reverse, 90, degrees);
}

void drivercontrol(void) {

  int deadband = 5;
  
  Controller1.ButtonL1.pressed(onevent_Controller1ButtonL1_pressed_0);
  wait(15, msec);
  Controller1.ButtonR2.pressed(onevent_Controller1ButtonR2_pressed_0);
  wait(15, msec);
  Controller1.ButtonR1.pressed(onevent_Controller1ButtonR1_pressed_0);
  wait(15, msec);
  
  while (true) {
    if (conveyorToggle == true) {
      ringMech.spin(forward);
      ringMech.setVelocity(100, percent);
    } else {
      ringMech.stop(brake);
    }

    //set speed variables to axis
    int leftMotorSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
    int rightMotorSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();

    //turns off left motors if in deadband range, otherwise sets to speed variable
    if (abs(leftMotorSpeed) < deadband) {
      leftMotor.setVelocity(0, percent);
    } else {
      leftMotor.setVelocity(leftMotorSpeed, percent);
    }
    //turns off right motors if in deadband range, otherwise sets to speed variable
    if (abs(rightMotorSpeed) < deadband) {
      rightMotor.setVelocity(0, percent);
    } else {
      rightMotor.setVelocity(rightMotorSpeed, percent);
    }

    leftMotor.spin(forward);
    rightMotor.spin(forward);

    wait(25, msec);
  }
}

//linear drive function
void drivelinear(int distance, directionType direction) {
  double time = distance/speed;
  driveTrain.spinFor(direction, time, sec);
}

//turning drive function
//call with turn([degrees], "[direction]");
void turn(int degreesvar, std::string direction) {
  double degreesFinal = degreesvar / 2;
  if(direction == "left") {
    leftMotor.spinFor(forward, 180, degrees, false);
    rightMotor.spinFor(reverse, 180, degrees);
  }
  if(direction == "right") {
    leftMotor.spinFor(reverse, 180, degrees, false);
    rightMotor.spinFor(forward, 180, degrees);
  }
}
  
// partial auton wp
void autonomous(void) {
  //set motor velocities so the motor actually goes zoom zoom
  leftMotor.setVelocity(100, percent);
  rightMotor.setVelocity(100, percent);
  ringMech.setVelocity(100, percent);
  ringMech.spinFor(forward, 690, degrees);
  /* leftMotor.spin(forward);
  rightMotor.spin(reverse);
  drivelinear(48, forward);
  ringMech.spinFor(forward, 360, degrees);
  drivelinear(24, reverse);
  turn(90, "left");
  drivelinear(24, forward);
  ringMech.spinFor(forward, 360, degrees);
  drivelinear(24, reverse);
  turn(90, "right");
  drivelinear(24, forward);
  ringMech.spinFor(forward, 360, degrees);
  Brain.Screen.print("test!!!"); */
}

int main() {
  Competition.drivercontrol(drivercontrol);
  Competition.autonomous(autonomous);

  return 0;

  //funni image drawing
  Brain.Screen.drawImageFromFile("image.bmp", 0, 0);

  // Initializing Robot Configuration. DO NOT REMOVE!    but what if i wanna remove it
  vexcodeInit();

    wait(25, msec);
}