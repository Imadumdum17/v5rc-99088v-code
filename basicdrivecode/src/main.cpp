#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  int deadband = 5;

  while (true) {
    int leftMotorSpeed =
        Controller1.Axis3.position() + Controller1.Axis1.position();
    int rightMotorSpeed =
        Controller1.Axis3.position() - Controller1.Axis1.position();

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

  if (Controller1.ButtonL1.pressing = true) {

  }
    

    wait(25, msec);
  }
}
