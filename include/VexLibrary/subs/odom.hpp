#pragma once

#include "VexLibrary/misc/globals.hpp"
#include "pros/rtos.hpp"
#include <vector>


namespace Lib {
class Chassis;
class OdomController;
}

namespace Lib {
class OdomController {
protected:
  Lib::Chassis *chassis;
  std::vector<double> left_prev;
  std::vector<double> right_prev;
  std::vector<int> tracking_prev;
  pros::Task *update_task = nullptr;
  double prev_heading = 0.0;

  void update();
  void update_prev();
  void update_loop(void *param);

  bool started = false;

public:
  OdomController(Lib::Chassis *chassis) : chassis(chassis) { this->init(); }
  void init();
  inline void start() {
    if (!this->started) {
      static pros::Task task = pros::Task([](void* cont){
        while (1) {
          ((OdomController*)cont)->update();
          pros::delay(Lib::DELAY);
        }
      }, (void*)this);
      this->update_task = &task;

      this->started = true;
    }
  };
};
} // namespace Lib
