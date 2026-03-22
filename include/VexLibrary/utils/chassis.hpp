#include "VexLibrary/Lib.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include <vector>

namespace Lib {
class Chassis {
protected:
  pros::MotorGroup *left_motors;
  pros::MotorGroup *right_motors;
  pros::IMU *imu;
  std::vector<TrackingWheel> tracking_wheels;
  float track_width;
  float wheel_diameter;

public:
  struct settings {
    pros::MotorGroup *left_motors = nullptr;
    pros::MotorGroup *right_motors = nullptr;
    pros::IMU *imu = nullptr;
    std::vector<TrackingWheel> tracking_wheels = {};
    float track_width = 0; // don't need if you have an IMU or 2 horizontal
                           // tracking wheels, only used to calculate heading
    float wheel_diameter = 0;
  };
  Chassis(settings s)
      : left_motors(s.left_motors), right_motors(s.right_motors), imu(s.imu),
        tracking_wheels(s.tracking_wheels), track_width(s.track_width),
        wheel_diameter(s.wheel_diameter) {}
};
} // namespace Lib
