#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/util.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <sys/_intsup.h>

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
pros::Motor motor1 (1, pros::v5::MotorGears::blue);
pros::Motor motor2 (2, pros::v5::MotorGears::blue);
pros::Motor motor3 (3, pros::v5::MotorGears::blue);
pros::Motor motor4 (4, pros::v5::MotorGears::blue);
pros::Motor motor5 (5, pros::v5::MotorGears::blue);
pros::Motor motor6 (6, pros::v5::MotorGears::blue);
pros::Vision vision1 (12);

pros::MotorGroup left_mg({1, 2, 3});
pros::MotorGroup right_mg({-4, -5, -6}); 
pros::MotorGroup drivebase({1, 2, 3, -4, -5, -6});
pros::Motor ringmech(7);
pros::Motor thethat(8);
pros::Imu imu(11);
pros::adi::Pneumatics clamp('A',false);

lemlib::Drivetrain drivetrain(&left_mg, &right_mg, 14.25, 2.75, 600, 2);
lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

// lateral PID controller
// to tune, move 48 inches, and adjust
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP) helps w/ oscilation
                                              0, // integral gain (kI) bounds of graph/max distance
                                              3, // derivative gain (kD) accel
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
// to tune, turn different angles and adjust
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
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

bool pressed2 = false;
void button2_pressed() {
	pressed2 = !pressed2;
	if (pressed2) {
		pros::lcd::set_text(2, "autonColor=red");
	} else {
		pros::lcd::set_text (2, "autonColour=blue");

	}
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	vision1.set_zero_point(E_VISION_ZERO_CENTER);
	chassis.calibrate();
	int skib = pros::usd::is_installed();
	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(button1_pressed);
	pros::lcd::register_btn1_cb(button2_pressed);
	pros::lcd::set_text(3, "oogly boogly");
	pros::lcd::set_text(4, "Ah, free at last. Oh, Gabriel, now dawns thy reckoning, and thy gore shall GLISTEN before the temples of man. Creature of steel, my gratitute upon thee for my freedom. But the crimes thy kind have commited against humanity are NOT forgotten. And thy punishment... is DEATH!");
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
	chassis.moveToPose(0, -30, 90, 5000); 
	/* drivebase.move(63);
	delay((26 / 86.6) / 500);
	drivebase.brake();
	clamp.toggle();
	if (pressed2 == false) {
		
	}
	pros::lcd::shutdown;
	
	pros::vision_object_s_t rtn = vision1.get_by_sig(0, 1);
	int xCoord = rtn.x_middle_coord;
	int yCoord = rtn.y_middle_coord;
	int sizeX = rtn.width;
	int sizeY = rtn.height;
	while (abs(yCoord + xCoord) < 80) {
		drivebase.move_relative(5, 1);
		if (sizeX * sizeY > 37500) { ringmech.move(127); 
			delay(1000); 
			ringmech.brake();
		}
	} 

	while (abs(yCoord + xCoord) > 79) { 
		left_mg.move(127); 
		right_mg.move(-127);
	 } */

	/* chassis.setPose(0, 0 , 0);
	thethat.move(127);
	delay(300);
	thethat.brake();
	chassis.moveToPoint(-7.496, 14.217, 5000);
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

	ringmech.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	thethat.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	while (true) {
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) { clamp.toggle(); }
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) { ringmech.move(-127); }
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) { ringmech.move(127); }
 
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) { thethat.move(-45); }
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) { thethat.move(127); }
		
		if (not master.get_digital(E_CONTROLLER_DIGITAL_UP) and not master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) { thethat.brake(); }
		if (not master.get_digital(E_CONTROLLER_DIGITAL_R1) and not master.get_digital(E_CONTROLLER_DIGITAL_R2)) { ringmech.brake(); } 

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