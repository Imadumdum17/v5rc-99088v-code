using namespace vex;

extern brain Brain;

extern controller Controller1;
extern motor FL;
extern motor FR;
extern motor BL;
extern motor BR;
extern motor_group LeftMotor;
extern motor_group RightMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);