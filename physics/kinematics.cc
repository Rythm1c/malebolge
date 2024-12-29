#include "kinematics.h"
#include "../math/vec3.h"

void simpleGravity(v3D &v) {
  // v = u + at
  // only affects the y component for a simple gravity simulation
  v3D gravity = v3D(0.0, -0.66, 0.0);
  v = (v + gravity);
}
