#pragma once

// includes
#include "pros/rtos.hpp"
#include <cmath>

// Full Library
namespace Lib {
// constants
static constexpr int DELAY = 10;

/**
 * @brief Proportional Integral Derivative (PID) controller.
 * Uses pros::millis() for timing — intended for use in a PROS environment.
 */
class PID {
protected:
  float Kp, Ki, Kd, windup_limit, target, current;
  float err = 0;
  float prev_err = 0;
  float total_err = 0;
  uint32_t prev_time = pros::millis();

public:
  /**
   * @brief PID controller configuration.
   * @param Kp Proportional gain.
   * @param Ki Integral gain.
   * @param Kd Derivative gain.
   * @param windup_limit Maximum absolute error for integral accumulation. Defaults to INFINITY (no limit).
   * @param target Target setpoint.
   * @param current Initial position.
   */
  struct settings {
    float Kp = 0;
    float Ki = 0;
    float Kd = 0;
    float windup_limit = INFINITY;
    float target = 0;
    float current = 0;
  };

  /**
   * @brief Construct a PID controller with the given settings.
   * @param s Controller settings.
   */
  PID(settings s)
      : Kp(s.Kp), Ki(s.Ki), Kd(s.Kd),
        windup_limit(s.windup_limit),
        target(s.target), current(s.current),
        err(s.target - s.current) {}

  // ── Getters ────────────────────────────────────────────────────────────────

  /// @brief Returns the proportional gain.
  inline float get_Kp() const { return this->Kp; }
  /// @brief Returns the integral gain.
  inline float get_Ki() const { return this->Ki; }
  /// @brief Returns the derivative gain.
  inline float get_Kd() const { return this->Kd; }
  /// @brief Returns the integral windup limit.
  inline float get_windup_limit() const { return this->windup_limit; }
  /// @brief Returns the current setpoint target.
  inline float get_target() const { return this->target; }
  /// @brief Returns the last measured position.
  inline float get_current() const { return this->current; }
  /// @brief Returns the current error (target - current).
  inline float get_error() const { return this->err; }
  /// @brief Returns the error from the previous update.
  inline float get_prev_error() const { return this->prev_err; }
  /// @brief Returns the accumulated integral error.
  inline float get_total_error() const { return this->total_err; }

  // ── Setters ────────────────────────────────────────────────────────────────

  /// @brief Sets the proportional gain.
  inline void set_Kp(float Kp) { this->Kp = Kp; }
  /// @brief Sets the integral gain.
  inline void set_Ki(float Ki) { this->Ki = Ki; }
  /// @brief Sets the derivative gain.
  inline void set_Kd(float Kd) { this->Kd = Kd; }
  /// @brief Sets the integral windup limit.
  inline void set_windup_limit(float windup_limit) { this->windup_limit = windup_limit; }
  /// @brief Sets the target setpoint.
  inline void set_target(float target) { this->target = target; }

  /**
   * @brief Updates all PID gains and windup limit from a settings struct.
   * @note Does not update target — use set_target() separately.
   * @param s New controller settings.
   */
  inline void set_pid(settings s) {
    this->set_Kp(s.Kp);
    this->set_Ki(s.Ki);
    this->set_Kd(s.Kd);
    this->set_windup_limit(s.windup_limit);
  }

  // ── Control ────────────────────────────────────────────────────────────────

  /**
   * @brief Resets integral and derivative state.
   * Call when reusing the controller for a new movement.
   */
  inline void reset() {
    this->err = 0;
    this->prev_err = 0;
    this->total_err = 0;
    this->prev_time = pros::millis();
  }

  /**
   * @brief Computes the PID output for the current position.
   * dt is calculated from the elapsed time since the last call to update().
   * @param pos Current measured position.
   * @return PID output value.
   */
  inline float update(float pos) {
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

    return (this->Kp * this->err) + (this->Kd * diff) + (this->Ki * this->total_err);
  }
};

bool init();
bool opcontrol();
bool auton();

} // namespace Lib