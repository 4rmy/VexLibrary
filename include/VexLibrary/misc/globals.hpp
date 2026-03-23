#pragma once

namespace Lib {

// constants
static constexpr int DELAY = 10;

void init();
void opcontrol();
void auton();

} // namespace Lib

// library callbacks to sync with VEX
inline void Lib::init() {}
inline void Lib::opcontrol() {}
inline void Lib::auton() {}
