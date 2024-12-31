#ifndef MESH_H
#define MESH_H

#include <array>
#include <iostream>
#include <vector>

#include "../math/mat4.h"
#include "../math/vec2.h"
#include "../math/vec3.h"

struct Vertex {
  p3D pos;
  Vector3f norm;
  Vector2f tc;
};

enum drawMode { POINTS, LINES, TRIANGLES };

struct Mesh {
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
