#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <array>

#include "../math/vec3.h"
#include "../math/vec2.h"
#include "../math/mat4.h"

struct Vertex
{
    p3D pos;
    v3D norm;
    v2D tc;
};

enum drawMode
{
    POINTS,
    LINES,
    TRIANGLES
};

struct Mesh
{
    uint VAO{0};
    uint VBO{0};
    uint EBO{0};

    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    drawMode mode{POINTS};

    void prepareRenderResources();
    void render();
    void clean();
};

#endif