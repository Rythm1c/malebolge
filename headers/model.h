#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include "../math/vec3.h"
#include "../math/quaternion.h"
#include "../math/mat4.h"

class Model
{
public:
    Model();
    ~Model() {}

    std::vector<struct Mesh> meshes;
    color3f color;

    void orient(Quat);
    void scale(v3D);
    void translate(v3D);

    void init();
    void render();
    void clean();

    mat4x4 get_transform();

private:
    class Transform *transform;
};

#endif