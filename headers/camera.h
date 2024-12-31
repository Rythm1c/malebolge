#ifndef CAMERA
#define CAMERA

#include "../math/mat4.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include <iostream>

class Camera {

public:
  Camera();
  ~Camera() {}

  float fov;
  Vector3f up;
  Vector3f pos;
  Vector3f front;
  float velocity;

  mat4x4 view();
  mat4x4 projection(float ratio);
  void rotation(const Vector2i &mousePos);

  void moveForwards(float);
  void moveBackwards(float);
  void moveLeft(float);
  void moveRight(float);

private:
  float pitch;
  float yaw;
};

#endif
