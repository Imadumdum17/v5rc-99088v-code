#include "vex.h"

using namespace vex;

//this line makes so much sense
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
double speed = 56.7; //inches per second

//forward and backward drive function
//call with drivelinear([distance in inches], [forward or backward]);
void drivelinear(double distance, directionType direction) {
  int time = distance/speed;
  LeftMotor.spin(direction);
  RightMotor.spin(direction);
  wait(time, sec);
  LeftMotor.stop(brake);
  RightMotor.stop(brake);
}

//auton function
void autonomous(void) {
  drivelinear(48, forward);
  LeftMotor.spinFor(forward, 90, degrees);
  RightMotor.spinFor(reverse, 90, degrees);
  Brain.Screen.print("skibidi!!!");
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
