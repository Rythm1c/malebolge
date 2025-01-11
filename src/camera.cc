#include "../headers/camera.h"
#include "../headers/world.h"
#include "../math/mat4.h"

Camera::Camera()
    : fov(45.0), up(Vector3f(0.0, 1.0, 0.0)), pos(Vector3f(0.0, 16.0, -20.0)),
      front(Vector3f(0.0, 0.0, 1.0)), velocity(40.0), pitch(0.0),
      yaw(to_radians(90.0f)) {}

Mat4x4 Camera::view()
{
  return look_at(this->pos, this->pos + this->front, this->up);
}
Mat4x4 Camera::projection(float ratio)
{
  return perspective(fov, ratio, 1e-1, 1e3);
}
void Camera::moveForwards(float delta)
{
  float speed = this->velocity * delta;
  this->pos += speed * this->front;
}
void Camera::moveBackwards(float delta)
{
  float speed = this->velocity * delta;
  this->pos -= speed * this->front;
}
void Camera::moveLeft(float delta)
{
  float speed = this->velocity * delta;
  Vector3f left = cross(this->up, this->front).unit();
  this->pos += speed * left;
}
void Camera::moveRight(float delta)
{
  float speed = this->velocity * delta;
  Vector3f left = cross(this->up, this->front).unit();
  this->pos -= speed * left;
}

void Camera::rotation(float x, float y)
{

  float xoffset = 0.15 * (float)(x);
  float yoffset = 0.15 * (float)(-y);

  this->yaw += to_radians(xoffset);
  this->pitch += to_radians(yoffset);

  clamp(this->pitch, to_radians(-89.0), to_radians(89.0));

  Vector3f newFront = Vector3f(0.0);

  newFront.x = cos(this->pitch) * cos(this->yaw);
  newFront.y = sin(this->pitch);
  newFront.z = cos(this->pitch) * sin(this->yaw);

  this->front = newFront.unit();
}
