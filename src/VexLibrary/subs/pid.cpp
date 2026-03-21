#include "VexLibrary/subs/pid.hpp"

// getters
float Lib::PID::get_Kp() const { return this->Kp; }
float Lib::PID::get_Ki() const { return this->Ki; }
float Lib::PID::get_Kd() const { return this->Kd; }
float Lib::PID::get_windup_limit() const { return this->windup_limit; }
float Lib::PID::get_target() const { return this->target; }
float Lib::PID::get_current() const { return this->current; }
float Lib::PID::get_error() const { return this->err; }
float Lib::PID::get_prev_error() const { return this->prev_err; }
float Lib::PID::get_total_error() const { return this->total_err; }

// setters
void Lib::PID::set_Kp(float Kp) { this->Kp = Kp; }
void Lib::PID::set_Ki(float Ki) { this->Ki = Ki; }
void Lib::PID::set_Kd(float Kd) { this->Kd = Kd; }
void Lib::PID::set_windup_limit(float windup_limit) {
  this->windup_limit = windup_limit;
}
void Lib::PID::set_target(float target) { this->target = target; }
void Lib::PID::set_pid(settings s) {
  this->set_Kp(s.Kp);
  this->set_Ki(s.Ki);
  this->set_Kd(s.Kd);
  this->set_windup_limit(s.windup_limit);
}
void Lib::PID::reset() {
  this->err = 0;
  this->prev_err = 0;
  this->total_err = 0;
  this->prev_time = pros::millis();
}

// Logic
float Lib::PID::update(float pos) {
  uint32_t now = pros::millis();
  float dt = (now - this->prev_time) / 1000.0f;
  this->prev_time = now;

  this->current = pos;
  this->err = this->target - this->current;

  if (fabs(this->err) <= this->windup_limit) {
    this->total_err += this->err * dt;
  }
  if ((this->err < 0 && this->prev_err > 0) ||
      (this->err > 0 && this->prev_err < 0)) {
    this->total_err = 0;
  }

  float diff = (this->err - this->prev_err) / dt;
  this->prev_err = this->err;

  return (this->Kp * this->err) + (this->Kd * diff) +
         (this->Ki * this->total_err);
}
