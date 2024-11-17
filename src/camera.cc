#include "../headers/camera.h"
#include "../headers/world.h"
#include "../math/mat4.h"

Camera::Camera()
    : fov(45.0),
      pitch(0.0),
      yaw(90.0f),
      velocity(0.0),
      up(v3D(0.0, 1.0, 0.0)),
      pos(v3D(0.0, 16.0, -20.0)),
      front(v3D(0.0, -0.4, 1.0)) {}

mat4x4 Camera::view()
{
    return look_at(this->pos, this->pos + this->front, this->up);
}
mat4x4 Camera::projection(float ratio)
{
    return perspective(fov, ratio, 1e-1, 1e3);
}
void Camera::moveForwards()
{
    this->pos += this->velocity * this->front;
}
void Camera::moveBackwards()
{
    this->pos -= this->velocity * this->front;
}
void Camera::moveLeft()
{
    this->pos += this->velocity * normalize(cross(this->up, this->front));
}
void Camera::moveRight()
{
    this->pos -= this->velocity * normalize(cross(this->up, this->front));
}

void Camera::rotation(const iv2D &mousePos)
{

    float xoffset = 0.15 * (float)(mousePos.x);
    float yoffset = 0.15 * (float)(-mousePos.y);

    this->yaw += xoffset;
    this->pitch += yoffset;

    clamp(this->pitch, -89.0, 89.0);

    v3D newFront = v3D(0.0);

    newFront.x = cos(to_radians(this->pitch)) * cos(to_radians(this->yaw));
    newFront.y = sin(to_radians(this->pitch));
    newFront.z = cos(to_radians(this->pitch)) * sin(to_radians(this->yaw));

    this->front = normalize(newFront);
}