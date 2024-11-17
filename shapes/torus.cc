#include "torus.h"
#include "../headers/mesh.h"

Torus::Torus(int divs, color3f col)
{
    color = col;
    float angle = 360.0 / ((float)divs - 1.0);

    mesh = new Mesh();
    Vertex vertex = {};
    mesh->mode = TRIANGLES;
    // inner radius = 0.3
    // outer radius = 0.7
    for (int i = 0; i < divs; i++)
    {
        float epsilon = to_radians(angle * (float)i);

        for (int j = 0; j < divs; j++)
        {
            float theta = to_radians(angle * (float)j);

            float hyp = 0.7 + 0.3 * std::cos(theta);

            float x = hyp * std::cos(epsilon);
            float y = 0.3 * std::sin(theta);
            float z = hyp * std::sin(epsilon);

            float nx = std::cos(theta) * std::cos(epsilon);
            float ny = std::sin(theta);
            float nz = std::cos(theta) * std::sin(epsilon);

            vertex.pos = v3D(x, y, z);
            vertex.norm = v3D(nx, ny, nz);

            mesh->vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < (divs - 1); i++)
    {
        for (int j = 0; j < divs; j++)
        {
            mesh->indices.push_back(i * divs + j);
            mesh->indices.push_back(i * divs + (j + 1) % divs);
            mesh->indices.push_back((i + 1) * divs + (j + 1) % divs);

            mesh->indices.push_back((i + 1) * divs + j);
            mesh->indices.push_back(i * divs + j);
            mesh->indices.push_back((i + 1) * divs + (j + 1) % divs);
        }
    }
}
