#include "uvsphere.h"
#include "../mesh.h"

Mesh *UVSphere(int longs, int lats, Color3f col)
{
  Mesh *result = new Mesh{.mode = TRIANGLES};

  clamp(longs, 0, 150);
  clamp(lats, 0, 150);

  float latAngle = 180.0 / float(lats - 1);
  float longAngle = 360.0 / float(longs - 1);

  Vertex vertex{.col = col};

  for (int i = 0; i < lats; i++)
  {
    float theta = to_radians(90.0 - ((float)i * latAngle));

    float y = sin(theta);

    vertex.tc.y = (float)i / float(lats - 1);

    for (int j = 0; j < longs; j++)
    {
      float epsilon = to_radians(j * longAngle);

      float x = cos(theta) * cos(epsilon);
      float z = cos(theta) * sin(epsilon);

      vertex.pos = {x, y, z};
      vertex.norm = vertex.pos;
      vertex.tc.x = (float)j / float(longs - 1);

      result->vertices.push_back(vertex);
    }
  }

  for (uint i = 0; i < (lats - 1); i++)
  {
    for (uint j = 0; j < longs; j++)
    {

      int currRow = i * longs;
      int nextRow = (i + 1) * longs;
      //........... nect row verts here
      //.       . .
      //.     .   .
      //.   .     .
      //. .       .
      //........... current row verts here

      // first triangle in quad
      result->indices.push_back(currRow + j);
      result->indices.push_back(nextRow + j);
      result->indices.push_back(nextRow + (j + 1) % longs);
      // second triangle in quad
      result->indices.push_back(currRow + j);
      result->indices.push_back(nextRow + (j + 1) % longs);
      result->indices.push_back(currRow + (j + 1) % longs);
    }
  }

  result->init();

  return result;
}