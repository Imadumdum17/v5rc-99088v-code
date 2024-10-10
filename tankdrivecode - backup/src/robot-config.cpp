#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller1 = controller(primary);
motor MotorFL = motor(PORT1, ratio18_1, true);
motor MotorBR = motor(PORT10, ratio18_1, false);
motor MotorFR = motor(PORT11, ratio18_1, false);
motor MotorBL = motor(PORT20, ratio18_1, true);
motor_group LeftMotor = motor_group(MotorFL, MotorBL);
motor_group RightMotor = motor_group(MotorFR, MotorBR);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
}



// trust this is what a motor group code looks like