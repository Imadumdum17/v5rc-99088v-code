#include "vex.h"
#include <iostream>
#include <string>

using namespace vex;

//this line makes so much sense
competition Competition;

int img = 3;
double speed = 56.7; //inches per second
bool conveyorToggle = false;

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

//forward and backward drive function
//call with drivelinear([distance in inches], [forward or backward]);
void drivelinear(double distance, directionType direction) {
  int time = distance/speed;
  leftMotor.spin(direction);
  rightMotor.spin(direction);
  wait(time, sec);
  leftMotor.stop(brake);
  rightMotor.stop(brake);
  Brain.Screen.print("skibidi!!!");
}

//turning drive function
//call with turn([degrees], "[direction]");
void turn(double degreesvar, std::string direction) {
  double degreesFinal = degreesvar / 2;
  if(direction == "left") {
    leftMotor.spinFor(forward, degreesFinal, degrees);
    rightMotor.spinFor(reverse, degreesFinal, degrees);
  }
  if(direction == "right") {
    leftMotor.spinFor(reverse, degreesFinal, degrees);
    rightMotor.spinFor(forward, degreesFinal, degrees);
  }
}

//auton function
void autonomous(void) {
  //set motor velocities so the motor actually goes zoom zoom
  leftMotor.setVelocity(100, percent);
  rightMotor.setVelocity(100, percent);
  leftMotor.spin(forward);
  rightMotor.spin(forward);
  wait(5, sec);
  drivelinear(12, forward);
  turn(90, "left");
  drivelinear(80, forward);
  turn(90, "right");
  drivelinear(8, forward);
  turn(90, "left");
  drivelinear(8, forward);
  drivelinear(1, reverse);
  turn(90, "left");
  drivelinear(100, forward);
}

//user control function
void usercontrol(void) {
   int deadband = 5;
}
int main() {
  Competition.autonomous(autonomous);
  while (true) {
    if (conveyorToggle == true) {
      ringMech.spin(forward);
      ringMech.setVelocity(100, percent);
    } else {
      ringMech.stop(brake);
    }
  Controller1.ButtonL1.pressed(onevent_Controller1ButtonL1_pressed_0);
  wait(15, msec);
  Controller1.ButtonR2.pressed(onevent_Controller1ButtonR2_pressed_0);
  wait(15, msec);
    Controller1.ButtonR1.pressed(onevent_Controller1ButtonR1_pressed_0);
  wait(15, msec);

  // Initializing Robot Configuration. DO NOT REMOVE!    but what if i wanna remove it
  vexcodeInit();

     wait(25, msec);
  }
}