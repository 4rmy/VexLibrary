#pragma once

namespace Lib {
class Pose {
protected:
  float x;     /// x position
  float y;     /// y position
  float theta; /// heading angle

public:
  /// settings struct for default constructor values
  struct settings {
    float x = 0;
    float y = 0;
    float theta = 0;
  };

  /// Pose contructor
  Pose(settings s) : x(s.x), y(s.y), theta(s.theta) {}

  /// @brief set the x value
  void set_x(float x);
  /// @brief set the y value
  void set_y(float y);
  /// @brief set the theta value
  void set_theta(float theta);
  /// @brief set the pose using settings
  void set_pose(settings s);

  /// @brief get the x value
  float get_x() const;
  /// @brief shorthand get_x
  inline float X() const { return this->get_x(); }
  /// @brief get the y value
  float get_y() const;
  /// @brief shorthand get_y
  inline float Y() const { return this->get_y(); }
  /// @brief get the theta value
  float get_theta() const;
  /// @brief shorthand get_theta
  inline float T() const { return this->get_theta(); }
};
} // namespace Lib