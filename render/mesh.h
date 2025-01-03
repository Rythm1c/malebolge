#ifndef MESH_H
#define MESH_H

#include <array>
#include <vector>

#include "../math/vec2.h"
#include "../math/vec3.h"

struct Vertex
{
  Point3f pos;
  Vector3f norm;
  Color3f col;
  Vector2f tc;
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

  void init();
  void render();
  void clean();
};

#endif
