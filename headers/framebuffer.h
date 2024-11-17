#ifndef _FRAMEBUFFER
#define _FRAMEBUFFER

#include <iostream>
#include <array>
#include "../math/vec4.h"
#include "../math/vec2.h"

class Framebuffer
{
private:
    uint VAO, VBO, EBO;
    uint FBO, RBO;
    std::array<v4D, 4> vertices;
    std::array<uint, 6> indices;
    v2D pos, area;

public:
    Framebuffer() {}
    ~Framebuffer() {}

    void load();
    void use();
    void detach();
    void clean();

    void reScale();
    void updateVertexData(v2D p, v2D a);

    // p(position): position of quad on screen
    // a(area): specify width and height of quad
    // call this function before the load function
    void loadQuad(v2D p, v2D a);
    void renderIntoQuad();

    float getQuadDimesnionsAspecRatio() { return (area.x / area.y); }

    uint frame;
};
#endif