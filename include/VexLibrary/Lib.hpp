#pragma once

// Full Library
namespace Lib {
  
// constants
static constexpr int DELAY = 10;

bool init();
bool opcontrol();
bool auton();

} // namespace Lib

// sub systems
#include "subs/pid.hpp" // PID controller
// ODOM controller (needs to be tied into init)
// Boomerang controller