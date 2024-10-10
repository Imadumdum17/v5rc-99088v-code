#include "vex.h"

using namespace vex;

competition Competition;

//input test
void onevent_Controller1ButtonA_pressed_0() {
  Controller1.Screen.print("the funni text ");
}
//also input test
void onevent_Controller1ButtonB_pressed_0() {
  Brain.Screen.print("test!!! ");
}

int img = 3;

//forward and backward drive function
//call with drivelinear([time], [sec or msec], [forward or backward]);
void drivelinear(int time, timeUnits unit, directionType direction) {
  LeftMotor.spin(direction);
  RightMotor.spin(direction);
  wait(time, unit);
  LeftMotor.stop(brake);
  RightMotor.stop(brake);
}

//auton function
void autonomous(void) {
  drivelinear(1.26984, sec, forward);
}

//user control function
void usercontrol(void) {

//when started/main function
}
int main() {
  //call auton and dc functions when auton/dc
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  //funni image drawing
  Brain.Screen.drawImageFromFile("image.bmp", 0, 0);

  //call input functions when input recieved
  Controller1.ButtonA.pressed(onevent_Controller1ButtonA_pressed_0);
  wait(15, msec);
  Controller1.ButtonB.pressed(onevent_Controller1ButtonB_pressed_0);
  wait(15, msec);

  // Initializing Robot Configuration. DO NOT REMOVE!    but what if i wanna remove it
  vexcodeInit();

  int deadband = 5;

  while (true) {
    //set speed variables to controller axis
    int leftMotorSpeed = Controller1.Axis3.position();
    int rightMotorSpeed = Controller1.Axis2.position();

    //turns off left motors if in deadband range, otherwise sets to speed variable
    if (abs(leftMotorSpeed) < deadband) {
      LeftMotor.setVelocity(0, percent);
    } else {
      LeftMotor.setVelocity(leftMotorSpeed, percent);
    }
    //turns off right motors if in deadband range, otherwise sets to speed variable
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
