#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/util.hpp"

using namespace pros;

ASSET(path_txt);

#define DIGITAL_SENSOR_PORT 'A'

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_mg({-1, -20});
pros::MotorGroup right_mg({7, 11}); 
pros::Motor intake(8);
pros::Motor conveyor(9);
pros::Motor thethat(6);
pros::Imu imu(2);
pros::adi::Pneumatics clamp('A',false);

lemlib::Drivetrain drivetrain(&left_mg, &right_mg, 9.75, 3.75, 333, 2);
lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(15, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              1500, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

void button1_pressed() {
	static bool pressed1 = false;
	pressed1 = !pressed1;
	if (pressed1) {
		pros::lcd::set_text(1, "driveStyle=tank");
	} else {
		pros::lcd::set_text(1, "driveStyle=curvatureSplit");

	}
}

void button2_pressed() {
	static bool pressed2 = false;
	pressed2 = !pressed2;
	if (pressed2) {
		pros::lcd::set_text(2, "winPointType=red");
	} else {
		pros::lcd::set_text (2, "winPointType=blue");

	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.calibrate();
	int skib = pros::usd::is_installed();
	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(button1_pressed);
	pros::lcd::register_btn1_cb(button2_pressed);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


void autonomous() {
	// chassis.turnToHeading(90, 100000);
	/* thethat.move(127);
	delay(300);
	thethat.brake();
	conveyor.move(127);
	delay(300);
	conveyor.brake();
	chassis.moveToPoint(0, 0, 5000);
	chassis.moveToPoint(0, 2.068, 5000);
	chassis.moveToPose(24.299, 15.251, 270, 5000);
	clamp.move(-127);
	delay(200);
	clamp.brake();
	conveyor.move(127);
	delay(500);
	conveyor.brake(); */
	 
	// chassis.setPose(0, 0, 0);
    // chassis.follow(path_txt, 2000, 15);
}

void opcontrol() {
	static bool pressed1 = false;

	conveyor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	thethat.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	while (true) {
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) { clamp.toggle(); // clamp.set_value(true); }
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) { conveyor.move(127); intake.move(-127); }
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) { conveyor.move(-127); intake.move(127); }
 
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) { thethat.move(-63); }
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) { thethat.move(127); }
		
		if (not master.get_digital(E_CONTROLLER_DIGITAL_UP) and not master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) { thethat.brake(); }
		if (not master.get_digital(E_CONTROLLER_DIGITAL_R1) and not master.get_digital(E_CONTROLLER_DIGITAL_R2)) { conveyor.brake(); intake.brake(); } 

		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		        // get left y and right x positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.curvature(leftY, rightX);
		pros::delay(20);            

	}
}
}