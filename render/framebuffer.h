#ifndef _FRAMEBUFFER
#define _FRAMEBUFFER

#include "../math/vec2.h"
#include "../math/vec4.h"
#include <array>

class Framebuffer
{
private:
  uint VAO, VBO, EBO;
  uint FBO, RBO;
  std::array<Vector4f, 4> vertices;
  std::array<uint, 6> indices;
  Vector2f pos, area;

public:
  Framebuffer() {}
  ~Framebuffer() {}

  void load();
  void use();
  void detach() const;
  void clean();

  void reScale();
  void updateVertexData(Vector2f p, Vector2f a);

  // p(position): position of quad on screen
  // a(area): specify width and height of quad
  // call this function before the load function
  void loadQuad(Vector2f p, Vector2f a);
  void renderIntoQuad();

  float getQuadDimesnionsAspecRatio() { return (area.x / area.y); }

  uint frame;
};
#endif
