#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
 /*
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
//	pros::lcd::initialize();
//	pros::lcd::set_text(1, "Hello PROS User!");

//	pros::lcd::register_btn1_cb(on_center_button);

//drive motors
pros::Motor lFDrive(10);
lFDrive.set_brake_mode(MOTOR_BRAKE_HOLD);
pros::Motor lRDrive(20);
lRDrive.set_brake_mode(MOTOR_BRAKE_HOLD);
pros::Motor rFDrive(1);
rFDrive.set_brake_mode(MOTOR_BRAKE_HOLD);
pros::Motor rRDrive(14);
rRDrive.set_brake_mode(MOTOR_BRAKE_HOLD);

//lift motors
pros::Motor lLift(7, true);
pros::Motor rLift(5);

//intake motors
pros::Motor lIntake(9, MOTOR_GEARSET_6, true);
pros::Motor rIntake(2, MOTOR_GEARSET_6);

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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);



	int liftSpeed = 200; //rpm
	int intakeSpeed = 500; //rpm
	while (true) {

	/*	pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
										 */

		int leftDrive = master.get_analog(ANALOG_LEFT_Y);
		int rightDrive = master.get_analog(ANALOG_RIGHT_Y);

		lFDrive = leftDrive;
		lRDrive = leftDrive;
		rFDrive = -rightDrive;
		rRDrive = -rightDrive;

	//
		if (master.get_digital(DIGITAL_R1) || master.get_digital(DIGITAL_L1)) {
			//move lift up
			lLift.move_velocity(liftSpeed);
			rLift.move_velocity(liftSpeed);
			//move intake in
			lIntake.move_velocity(intakeSpeed);
			rIntake.move_velocity(intakeSpeed);

		}
		else if (master.get_digital(DIGITAL_R2) || master.get_digital(DIGITAL_L2)) {
			//move lift down
			lLift.move_velocity(-liftSpeed);
			rLift.move_velocity(-liftSpeed);
			//move intake out
			lIntake.move_velocity(-intakeSpeed);
			rIntake.move_velocity(-intakeSpeed);
		}
		else{
			//stop both lift and intake
			lLift.move_velocity(0);
			rLift.move_velocity(0);

			lIntake.move_velocity(0);
			rIntake.move_velocity(0);
		}


		pros::delay(10);
	}
}
