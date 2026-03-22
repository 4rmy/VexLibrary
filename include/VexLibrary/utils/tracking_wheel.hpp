#include "api.h"

namespace Lib {
class TrackingWheel {
protected:
  pros::Rotation *encoder;
  float dist;
  float angle;

public:
  struct settings {
    pros::Rotation *encoder;
    float dist;
    float angle;
  };
  struct settings_noangle {
    pros::Rotation *encoder;
    float dist;
    bool reversed = false;
  };
  // constructors
  TrackingWheel(settings s)
      : encoder(s.encoder), dist(s.dist), angle(s.angle) {}
  TrackingWheel HorizontalTrackingWheel(settings_noangle s) {
    return TrackingWheel({.encoder = s.encoder,
                          .dist = s.dist,
                          .angle = (float)((s.reversed) ? 180 : 0)});
  }
  TrackingWheel VerticalTrackingWheel(settings_noangle s) {
    return TrackingWheel({.encoder = s.encoder,
                          .dist = s.dist,
                          .angle = (float)(90. * ((s.reversed) ? -1 : 1))});
  }
};
} // namespace Lib