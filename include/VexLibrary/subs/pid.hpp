#include "pros/rtos.hpp"
#include <cmath>

namespace Lib {

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
   * @param windup_limit Maximum absolute error for integral accumulation.
   * Defaults to INFINITY (no limit).
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
      : Kp(s.Kp), Ki(s.Ki), Kd(s.Kd), windup_limit(s.windup_limit),
        target(s.target), current(s.current), err(s.target - s.current) {}

  // ── Getters ────────────────────────────────────────────────────────────────

  /// @brief Returns the proportional gain.
  float get_Kp() const;
  /// @brief Returns the integral gain.
  float get_Ki() const;
  /// @brief Returns the derivative gain.
  float get_Kd() const;
  /// @brief Returns the integral windup limit.
  float get_windup_limit() const;
  /// @brief Returns the current setpoint target.
  float get_target() const;
  /// @brief Returns the last measured position.
  float get_current() const;
  /// @brief Returns the current error (target - current).
  float get_error() const;
  /// @brief Returns the error from the previous update.
  float get_prev_error() const;
  /// @brief Returns the accumulated integral error.
  float get_total_error() const;

  // ── Setters ────────────────────────────────────────────────────────────────

  /// @brief Sets the proportional gain.
  void set_Kp(float Kp);
  /// @brief Sets the integral gain.
  void set_Ki(float Ki);
  /// @brief Sets the derivative gain.
  void set_Kd(float Kd);
  /// @brief Sets the integral windup limit.
  void set_windup_limit(float windup_limit);
  /// @brief Sets the target setpoint.
  void set_target(float target);

  /**
   * @brief Updates all PID gains and windup limit from a settings struct.
   * @note Does not update target — use set_target() separately.
   * @param s New controller settings.
   */
  void set_pid(settings s);

  // ── Control ────────────────────────────────────────────────────────────────

  /**
   * @brief Resets integral and derivative state.
   * Call when reusing the controller for a new movement.
   */
  void reset();

  /**
   * @brief Computes the PID output for the current position.
   * dt is calculated from the elapsed time since the last call to update().
   * @param pos Current measured position.
   * @return PID output value.
   */
  float update(float pos);
};

} // namespace Lib