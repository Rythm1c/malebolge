// computed textures to make everything pretty

#ifndef TEXTURES_H
#define TEXTURES_H

#include "../math/vec3.h"

class Texture;
Texture *createGridTexture(
    int w, int h, Color3f main, Color3f lines,
    int lats, int longs, float thickness);

Texture *createCheckeredTexture(
    int w, int h, Color3f first, Color3f second, int divs);

#endif