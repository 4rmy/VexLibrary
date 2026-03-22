#pragma once

namespace Lib {

// constants
static constexpr int DELAY = 10;

void init();
void opcontrol();
void auton();

} // namespace Lib

// utilities
#include "utils/pose.hpp"           // position + heading
#include "utils/tracking_wheel.hpp" // tracking wheels

// sub systems
#include "subs/pid.hpp" // PID controller

// library callbacks to sync with VEX
inline void Lib::init() {}
inline void Lib::opcontrol() {}
inline void Lib::auton() {}