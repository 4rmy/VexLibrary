#include "VexLibrary/utils/pose.hpp"

void Lib::Pose::set_x(float x) { this->x = x; };
void Lib::Pose::set_y(float y) { this->y = y; };
void Lib::Pose::set_theta(float theta) { this->theta = theta; };
void Lib::Pose::set_pose(settings s) {
  this->x = s.x;
  this->y = s.y;
  this->theta = s.theta;
}

float Lib::Pose::get_x() const { return this->x; };
float Lib::Pose::get_y() const { return this->y; };
float Lib::Pose::get_theta() const { return this->theta; };