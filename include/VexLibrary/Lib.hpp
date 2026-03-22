#pragma once

namespace Lib {

// constants
static constexpr int DELAY = 10;

bool init();
bool opcontrol();
bool auton();

} // namespace Lib

// utilities
#include "utils/pose.hpp" // position + heading
#include "utils/tracking_wheel.hpp" // tracking wheels

// sub systems
#include "subs/pid.hpp" // PID controller
