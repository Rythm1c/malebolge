#ifndef CAMERA
#define CAMERA

#include "../math/mat4.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include <iostream>

class Camera
{

public:
  Camera();
  ~Camera() {}

  float fov;
  Vector3f up;
  Vector3f pos;
  Vector3f front;
  float velocity;

  Mat4x4 view();
  Mat4x4 projection(float ratio);
  void rotation(float x, float y);

  void moveForwards(float);
  void moveBackwards(float);
  void moveLeft(float);
  void moveRight(float);

private:
  float pitch;
  float yaw;
};

#endif
