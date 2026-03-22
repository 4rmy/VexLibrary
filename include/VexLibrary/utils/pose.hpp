namespace Lib {
class Pose {
protected:
  float x, y, theta;

public:
  struct settings {
    float x = 0;
    float y = 0;
    float theta = 0;
  };

  Pose(settings s) : x(s.x), y(s.y), theta(s.theta) {}

  void set_x(float x);
  void set_y(float y);
  void set_theta(float theta);
  void set_pose(settings s);

  float get_x() const;
  float get_y() const;
  float get_theta() const;
};
} // namespace Lib