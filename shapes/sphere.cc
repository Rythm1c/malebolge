#include "sphere.h"
#include "../render/mesh.h"
#include "shape.h"

Sphere::Sphere(float rad, int longs, int lats, Color3f col) : radius(rad)
{
  color = col;
  mesh = new Mesh();
  this->transform.scaling = {radius, radius, radius};

  clamp(longs, 0, 150);
  clamp(lats, 0, 150);

  float latAngle = 180.0f / (float)(lats - 1);
  float longAngle = 360.0f / (float)(longs - 1);

  Vertex vertex = {};

  mesh->mode = TRIANGLES;

  for (int i = 0; i < lats; i++)
  {
    float theta = 90.0f - ((float)i * latAngle);

    float y = sin(to_radians(theta));

    vertex.tc.y = (float)i / (float)(lats - 1);

    for (int j = 0; j < longs; j++)
    {
      float epsilon = j * longAngle;

      float x = cos(to_radians(theta)) * cos(to_radians(epsilon));
      float z = cos(to_radians(theta)) * sin(to_radians(epsilon));

      vertex.pos = {x, y, z};
      vertex.norm = vertex.pos;
      vertex.tc.x = (float)j / (float)(longs - 1);

      mesh->vertices.push_back(vertex);
    }
  }

  for (uint i = 0; i < (lats - 1); i++)
  {

    for (uint j = 0; j < longs; j++)
    {
      mesh->indices.push_back(i * longs + j);
      mesh->indices.push_back(i * longs + (j + 1) % longs);
      mesh->indices.push_back((i + 1) * longs + (j + 1) % longs);

      mesh->indices.push_back((i + 1) * longs + j);
      mesh->indices.push_back(i * longs + j);
      mesh->indices.push_back((i + 1) * longs + (j + 1) % longs);
    }
  }
}
