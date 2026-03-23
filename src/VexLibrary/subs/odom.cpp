#include <vector>

#include "VexLibrary/Lib.hpp"
#include "VexLibrary/subs/odom.hpp"
#include "VexLibrary/utils/chassis.hpp"

void Lib::OdomController::init() {
  this->left_prev = std::vector<double>(this->chassis->left_motors->size());
  this->right_prev = std::vector<double>(this->chassis->right_motors->size());
  this->tracking_prev = std::vector<int>(this->chassis->tracking_wheels.size());

  this->update_prev();
}

void Lib::OdomController::update_prev() {
  // store new prev positions
  // left motors
  size_t i = 0;
  for (auto p : this->chassis->left_motors->get_position_all()) {
    this->left_prev[i] = p;
  }
  // right motors
  i = 0;
  for (auto p : this->chassis->right_motors->get_position_all()) {
    this->right_prev[i] = p;
  }
  // tracking wheels
  for (auto w : this->chassis->tracking_wheels) {
    this->left_prev[i] = w.get_pos();
  }
  this->prev_heading = this->chassis->imu->get_heading();
}

void Lib::OdomController::update() {
  // setup
  Lib::Pose prev_pose = this->chassis->get_pose();
  Lib::Pose new_pose = Lib::Pose({});

  // calculate new pose

  // set prev
  this->update_prev();
  // set the chassis pose
  this->chassis->pose.set_pose(
      {.x = new_pose.X(), .y = new_pose.Y(), .theta = new_pose.T()});
}
