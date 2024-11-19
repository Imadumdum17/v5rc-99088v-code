#include "vex.h"
#include <iostream>
#include <string>

using namespace vex;

//this line makes so much sense
competition Competition;

int img = 3;
double speed = 56.7; //inches per second
bool conveyorToggle = false;
bool conveyorReverseToggle = false;

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
  Brain.Screen.print("skibidi!!!");
}

//user control function
void usercontrol(void) {

//when started/main function
}
int main() {
  conveyorToggle = false;

  //call auton and dc functions when auton/dc
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  //funni image drawing
  Brain.Screen.drawImageFromFile("image.bmp", 0, 0);

  Controller1.ButtonL1.pressed(onevent_Controller1ButtonL1_pressed_0);
  wait(15, msec);
  Controller1.ButtonR2.pressed(onevent_Controller1ButtonR2_pressed_0);
  wait(15, msec);
    Controller1.ButtonR1.pressed(onevent_Controller1ButtonR1_pressed_0);
  wait(15, msec);

  // Initializing Robot Configuration. DO NOT REMOVE!    but what if i wanna remove it
  vexcodeInit();

  int deadband = 5;

  while (true) {
    if (conveyorToggle == true) {
      ringMech.spin(forward);
      ringMech.setVelocity(100, percent);
    } else {
      ringMech.stop(brake);
    }

    //set speed variables to controller axis
    int leftMotorSpeed = Controller1.Axis3.position();
    int rightMotorSpeed = Controller1.Axis2.position();

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