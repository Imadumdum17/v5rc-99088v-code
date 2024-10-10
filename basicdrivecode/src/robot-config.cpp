#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller1 = controller(primary);
motor LeftMotor = motor(PORT1, ratio18_1, false);
motor RightMotor = motor(PORT10, ratio18_1, true);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
}