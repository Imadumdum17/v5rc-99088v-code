#include "vex.h"

using namespace vex;

void onevent_Controller1ButtonA_pressed_0() {
  Controller1.Screen.print("the funni text ");
}

void onevent_Controller1ButtonB_pressed_0() {
  Brain.Screen.print("test!!!");
}

int main() {

  Controller1.ButtonA.pressed(onevent_Controller1ButtonA_pressed_0);
  wait(15, msec);

    Controller1.ButtonB.pressed(onevent_Controller1ButtonB_pressed_0);
  wait(15, msec);

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  int deadband = 5;

  while (true) {
    int leftMotorSpeed = Controller1.Axis3.position();
    int rightMotorSpeed = Controller1.Axis2.position();

    if (abs(leftMotorSpeed) < deadband) {
      LeftMotor.setVelocity(0, percent);
    } else {
      LeftMotor.setVelocity(leftMotorSpeed, percent);
    }

    if (abs(rightMotorSpeed) < deadband) {
      RightMotor.setVelocity(0, percent);
    } else {
      RightMotor.setVelocity(rightMotorSpeed, percent);
    }

    LeftMotor.spin(forward);
    RightMotor.spin(forward);

    wait(25, msec);
  }
}