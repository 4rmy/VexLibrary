#pragma once

#include "VexLibrary/subs/odom.hpp"
#include "VexLibrary/utils/pose.hpp"
#include "VexLibrary/utils/tracking_wheel.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include <vector>

namespace Lib {
class Chassis {
  friend class OdomController;

protected:
  pros::MotorGroup *left_motors;
  pros::MotorGroup *right_motors;
  pros::IMU *imu;
  std::vector<TrackingWheel> tracking_wheels;
  float track_width;
  float wheel_diameter;

  Lib::Pose pose;
  Lib::OdomController odom;

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
        wheel_diameter(s.wheel_diameter), pose(Lib::Pose({0, 0, 0})),
        odom(Lib::OdomController(this)) {}

  inline Lib::Pose get_pose() const { return this->pose; }
};
} // namespace Lib
