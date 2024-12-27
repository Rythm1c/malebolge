#include "../headers/camera.h"
#include "../headers/world.h"
#include "../math/mat4.h"

Camera::Camera()
    : fov(45.0), up(v3D(0.0, 1.0, 0.0)), pos(v3D(0.0, 16.0, -20.0)),
      front(v3D(0.0, 0.0, 1.0)), velocity(40.0), pitch(0.0),
      yaw(to_radians(90.0f)) {}

mat4x4 Camera::view() {
  return look_at(this->pos, this->pos + this->front, this->up);
}
mat4x4 Camera::projection(float ratio) {
  return perspective(fov, ratio, 1e-1, 1e3);
}
void Camera::moveForwards(float delta) {
  float speed = this->velocity * delta;
  this->pos += speed * this->front;
}
void Camera::moveBackwards(float delta) {
  float speed = this->velocity * delta;
  this->pos -= speed * this->front;
}
void Camera::moveLeft(float delta) {
  float speed = this->velocity * delta;
  v3D left = normalize(cross(this->up, this->front));
  this->pos += speed * left;
}
void Camera::moveRight(float delta) {
  float speed = this->velocity * delta;
  v3D left = normalize(cross(this->up, this->front));
  this->pos -= speed * left;
}

void Camera::rotation(const iv2D &mousePos) {

  float xoffset = 0.15 * (float)(mousePos.x);
  float yoffset = 0.15 * (float)(-mousePos.y);

  this->yaw += to_radians(xoffset);
  this->pitch += to_radians(yoffset);

  clamp(this->pitch, to_radians(-89.0), to_radians(89.0));

  v3D newFront = v3D(0.0);

  newFront.x = cos(this->pitch) * cos(this->yaw);
  newFront.y = sin(this->pitch);
  newFront.z = cos(this->pitch) * sin(this->yaw);

  this->front = normalize(newFront);
}
