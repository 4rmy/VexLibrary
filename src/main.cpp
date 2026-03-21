#include "main.h"
#include "Lib.h" // IWYU: keep


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {

	while (true) {
		
		pros::delay(Lib::DELAY);                               // Run for 20 ms then update
	}
}