#include "cubeSphere.h"
#include "../mesh.h"

void addFace(
    Mesh &mesh, Vector3f start, Vector3f stepX,
    Vector3f stepY, int steps, Color3f color);

void calcIndices(Mesh &, int);

Mesh CubeSpere(int divs, Color3f colors[6])
{

  Mesh result = Mesh{.mode = TRIANGLES};

  float step = 2.0 / float(divs);

  // add  -Z face values
  addFace(
      result, Vector3f(-1.0, -1.0, -1.0), Vector3f(step, 0.0, 0.0),
      Vector3f(0.0, step, 0.0), divs, colors[0]);
  // add  +Z face values
  addFace(
      result, Vector3f(-1.0, -1.0, 1.0), Vector3f(step, 0.0, 0.0),
      Vector3f(0.0, step, 0.0), divs, colors[1]);
  // add  -X face values
  addFace(
      result, Vector3f(-1.0, -1.0, -1.0), Vector3f(0.0, 0.0, step),
      Vector3f(0.0, step, 0.0), divs, colors[2]);
  // add  +X face values
  addFace(
      result, Vector3f(1.0, -1.0, -1.0), Vector3f(0.0, 0.0, step),
      Vector3f(0.0, step, 0.0), divs, colors[3]);
  // add  -Y face values
  addFace(
      result, Vector3f(-1.0, -1.0, -1.0), Vector3f(step, 0.0, 0.0),
      Vector3f(0.0, 0.0, step), divs, colors[4]);
  // add  +Y face values
  addFace(
      result, Vector3f(-1.0, 1.0, -1.0), Vector3f(step, 0.0, 0.0),
      Vector3f(0.0, 0.0, step), divs, colors[5]);

  calcIndices(result, divs + 1);

  result.init();

  return result;
}

void addFace(
    Mesh &mesh, Vector3f start, Vector3f stepX,
    Vector3f stepY, int steps, Color3f color)
{

  for (int i = 0; i <= steps; i++)
  {

    for (int j = 0; j <= steps; j++)
    {

      Vector3f w = stepX * float(j);
      Vector3f h = stepY * float(i);

      Vector3f pos = normalize(start + w + h);

      float s = float(j) / float(steps);
      float t = float(i) / float(steps);
      // add  Z- face values
      Vertex vertex{};
      vertex.pos = pos;
      vertex.norm = pos;
      vertex.col = color;
      vertex.tc = Vector2f(s, t);

      mesh.vertices.push_back(vertex);
    }
  }
}

void calcIndices(Mesh &mesh, int divs)
{

  for (int i = 0; i < 6; i++) // all six faces accounted for
  {
    for (int j = 0; j < (divs - 1); j++)
    {
      for (int k = 0; k < (divs - 1); k++)
      {
        // first and second row
        int currRow = i * divs * divs + j * divs;
        int nextRow = i * divs * divs + (j + 1) * divs;

        //........... next row verts here
        //.       . .
        //.     .   .
        //.   .     .
        //. .       .
        //........... current row verts here

        // first triangle
        mesh.indices.push_back(currRow + k);
        mesh.indices.push_back(nextRow + k);
        mesh.indices.push_back(nextRow + k + 1);
        // second triangle
        mesh.indices.push_back(currRow + k);
        mesh.indices.push_back(nextRow + k + 1);
        mesh.indices.push_back(currRow + k + 1);
      }
    }
  }
}
