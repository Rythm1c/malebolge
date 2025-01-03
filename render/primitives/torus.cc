#include "torus.h"
#include "../mesh.h"

Mesh Torus(int divs, Color3f col)
{

  float angle = 360.0 / ((float)divs - 1.0);

  Mesh final{.mode = TRIANGLES};
  Vertex vertex{};
  // inner radius = 0.3
  // outer radius = 0.7
  for (int i = 0; i < divs; i++)
  {
    float epsilon = to_radians(angle * (float)i);

    for (int j = 0; j < divs; j++)
    {
      float theta = to_radians(angle * (float)j);

      float hyp = 0.7 + 0.3 * cos(theta);

      float x = hyp * cos(epsilon);
      float y = 0.3 * sin(theta);
      float z = hyp * sin(epsilon);

      float nx = cos(theta) * cos(epsilon);
      float ny = sin(theta);
      float nz = cos(theta) * sin(epsilon);

      vertex.pos = Vector3f(x, y, z);
      vertex.norm = Vector3f(nx, ny, nz);

      final.vertices.push_back(vertex);
    }
  }

  for (int i = 0; i < (divs - 1); i++)
  {
    for (int j = 0; j < divs; j++)
    {
      int currRow = i * divs;
      int nextRow = (i + 1) * divs;
      //........... nect row verts here
      //.       . .
      //.     .   .
      //.   .     .
      //. .       .
      //........... current row verts here

      // first triangle in quad
      final.indices.push_back(currRow + j);
      final.indices.push_back(nextRow + j);
      final.indices.push_back(nextRow + (j + 1) % divs);
      // second triangle in quad
      final.indices.push_back(currRow + j);
      final.indices.push_back(nextRow + (j + 1) % divs);
      final.indices.push_back(currRow + (j + 1) % divs);
    }
  }

  final.init();

  return final;
}