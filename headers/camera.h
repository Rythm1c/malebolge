#ifndef CAMERA
#define CAMERA

#include <iostream>
#include "../math/mat4.h"
#include "../math/vec3.h"
#include "../math/vec2.h"

class Camera
{

public:
    Camera();
    ~Camera() {}

    float fov;
    v3D up;
    v3D pos;
    v3D front;
    float velocity;

    mat4x4 view();
    mat4x4 projection(float ratio);
    void rotation(const iv2D &mousePos);

    void moveForwards(float);
    void moveBackwards(float);
    void moveLeft(float);
    void moveRight(float);

private:
    float pitch;
    float yaw;
};

#endif