#include "main.h"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include "pros/motors.hpp"
#include "pros/vision.hpp"

using namespace pros;


#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT -5
#define ARM_PORT 4
#define CLAW_PORT 7

/**
 * A callback functio	6n for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
	Motor left_wheels (LEFT_WHEELS_PORT);
	Motor right_wheels (RIGHT_WHEELS_PORT);

	// Claw and arm definitions
	Motor claw (CLAW_PORT);
	Motor arm (ARM_PORT);
	arm.set_brake_mode(MOTOR_BRAKE_HOLD);

	// Controller definitions
	Controller master (CONTROLLER_MASTER);

	
//======================================================================================
//============================ Bumper Sensor ===========================================
//======================================================================================

	// Define a button called bumperSensor on ADI (Analog/Digital Interface) port A
	ADIButton bumperSensor('A');

/* 	// Example 1: Turn motor off when bumper is pressed, otherwise motors spin forward
	while (true) {
		if (bumperSensor.get_value() == 1) { // If the bumper is pressed
			left_wheels.move_velocity(0);
			right_wheels.move_velocity(0);
		} else {
			left_wheels.move(127); // Move forward at full speed
			right_wheels.move(127);
		}
		pros::delay(10);
	} 
*/


/*	
	// Example 2: Move motors forward and toggles on and off when bumper is pressed
	bool motorsOn = false; // Current state of the motors
	bool lastBumperState = false; // Last state of the bumper

	while (true) {
		bool isPressed = bumperSensor.get_value(); // Read the current state of the bumper

		// Check bumper is pressed and was not pressed last time, switch motors' state
		if ((isPressed == true) && (lastBumperState == false)) {
			motorsOn = !motorsOn; // Toggle the motors' state
		}

		if (motorsOn) {
			left_wheels.move_velocity(100); // Move forward at 100% speed
			right_wheels.move_velocity(100);
		} else {
			left_wheels.move_velocity(0); // Stop the motors
			right_wheels.move_velocity(0);
		}

		lastBumperState = isPressed; // Update last state
		delay(10);
	} 
*/
	

//======================================================================================
//============================ Rotation Sensor =========================================
//======================================================================================

	Rotation rotation_sensor(10);  

/*  
 	// This is a simple program that rotates the arm 90 degrees
	// After running this example, try accomplishing the same task with motor encoding
	rotation_sensor.reset_position();


	int target_degrees = 90;   // 90 degrees
	int speed = rotation_sensor.get_velocity(); // in centidegrees
	
	double current_angle = rotation_sensor.get_position() / 100;
	if (current_angle > 180) {
		current_angle -= 360;
	}

	lcd::print(2, "Initial Angle: %.2f deg/s", current_angle); // print speed on line 0


	while (current_angle < target_degrees) {
		speed = rotation_sensor.get_velocity();
		current_angle = rotation_sensor.get_position() / 100;
		if (current_angle > 180) {
			current_angle -= 360;
		}
		
		lcd::print(0, "Angle: %.2f deg/s", current_angle); // print speed on line 0
		lcd::print(1, "Speed: %d deg/s", speed); // print speed on line 0

		arm.move(50);
		delay(10);  
	}

	// Stop motors when target reached
	arm.brake(); 
*/
 	

 /*
	Practice: 
		1) Try to do this same example but with motor encoding 
			Hint: the driving motor is 12 tooth and the driven gear is 84 tooth
		2) Edit the code so that the speed of which the motor moves is proportionate to how far the current angle is to the target
			- ie: faster when far from target and slower when close to target
*/

//======================================================================================
//============================ Optical Sensor   =========================================
//======================================================================================

/*
Optical opticalSensor(3); // Create an optical sensor on port 3
opticalSensor.set_led_pwm(100); // Set the brightness of the LED to 100% (adjust as needed)

 
while (true) {
	double hue = opticalSensor.get_hue(); // Get the hue value
	lcd::print(0, "Hue: %.2f", hue); // Print the hue value on line 0

	delay(100); // Delay for a short period to avoid flooding the LCD
}
*/

// 1) What is the range of the hue values?
// 2) Find a range of hue values for the red and blue balls
// 3) Have the robot drive forward until it sees a red ball, then stop
// 4) Have the robot stationary until it sees a blue ball, then drive forward


//======================================================================================
//============================ Vision Sensor   =========================================
//======================================================================================

/* 
AIVision::Color color = {}
	uint8_t id;             // id of color descriptor, can range from 1-7 
	uint8_t red;            // red value of color 
	uint8_t green;          // green value of color 
	uint8_t blue;           // blue value of color 
	float hue_range;        // range by which detected color's hue can vary from the base color, can range from 1-40 
	float saturation_range; // range by which detected color's saturation can vary from base color, can range from 0.1-1 
}
*/

/* 
 	AIVision ai_vision(6);
	ai_vision.reset(); // Reset the AI Vision sensor
	ai_vision.start_awb(); // Start auto white balance
	AIVision::Color redBlock = {1, 255, 0, 0, 10.00, 0.20}; // Define a color to detect (red in this case)
	AIVision::Color blueBlock = {2, 0, 200, 255, 20.00, 0.20}; // Define a color to detect (blue in this case)
	ai_vision.set_color(blueBlock); // Set a color to start detecting 

	//obj.object.color.height
	double currWidth = 0;
	double lastWidth = 0;
	bool isObjectDetected = false; // Flag to check if an object is detected

	while (true) {
		AIVision::Object obj = ai_vision.get_object(0); // Get the first detected object

		currWidth = obj.object.color.width;
		if (currWidth == lastWidth) {
			lcd::print(0, "Nothing there!");
			isObjectDetected = false;
			//acontinue;
		}
		else {
			lastWidth = currWidth;
			lcd::print(0, "Detected Object!");
			isObjectDetected = true;
		}

		lcd::print(1, "The height is %d", obj.object.color.height);
		lcd::print(2, "The width is %d", obj.object.color.width);
 		lcd::print(3, "The x_offset is %d", obj.object.color.xoffset);
		lcd::print(4, "The y_offset is %d", obj.object.color.yoffset); 

		double x = 0; // Calculate the center x position
		double y = 0; // Calculate the center y position
		lcd::print(5, "Center X: %.2f", x);
		lcd::print(6, "Center Y: %.2f", y);

		double correctedX = x;
		double correctedY = y;
		lcd::print(5, "Corrected X: %.2f", correctedX);
		lcd::print(6, "Corrected Y: %.2f", correctedY);
		
		delay(50);
	}

 */

	// 1) What do x and y offset mean? Use this to calculate the center of the object. Save it into x and y variables
	// 2) Find the size of the screen (Hint: What are the max and min values of the offsets?)
	// 3) Find a way to correct the x and y values to have 0,0 be the center of the screen 
	// 4) Here comes the fun part! Use the x and y values to move the robot chase the robot!

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
	// Drivetrian definitions
	Motor left_wheels (LEFT_WHEELS_PORT);
	Motor right_wheels (RIGHT_WHEELS_PORT);

	// Claw and arm definitions
	Motor claw (CLAW_PORT);
	Motor arm (ARM_PORT);
	arm.set_brake_mode(MOTOR_BRAKE_HOLD);

	// Controller definitions
	Controller master (CONTROLLER_MASTER);

	while (true) {

		// Set the left and right wheels to move based on the left and right analog sticks
		int power = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		// What input from the controller will control the turning?
		int left = power + turn;
		int right = power - turn;
		
		left_wheels.move(left);
		right_wheels.move(right);

		// Set the arm to move based on the left bumpers
		if (master.get_digital(DIGITAL_L1)) {
			arm.move_velocity(100);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			arm.move_velocity(-100);
		}
		else {
			arm.move_velocity(0);
		}

		// Set the claw to move based on the right bumpers
		if (master.get_digital( DIGITAL_R1 )) {
			claw.move_velocity(100);
		}
		else if (master.get_digital(DIGITAL_R2)) {
			claw.move_velocity(-100);
		}
		else {
			claw.move_velocity(0);
		}

		pros::delay(2);
	}
}
