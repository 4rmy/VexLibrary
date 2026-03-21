#include "main.h"

// include the library
#include "VexLibrary/Lib.hpp" // IWYU: keep

void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {

  while (true) {

    pros::delay(Lib::DELAY);
  }
}