#include "textures.h"
#include "texture.h"
#include "../math/math.h"

Texture *createGridTexture(
    int w, int h, Color3f main, Color3f line,
    int lats, int longs, float thickness)
{
  unsigned char *gridlines = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

  Texture *tex = new Texture();

  // 1.0 => 255 => ff
  for (int i = 0; i < h; i++)
  {

    for (int j = 0; j < w; j++)
    {
      // std::cout << i << " " << j << std::endl;

      float latDivs = 1.0 / lats;
      float longDivs = 1.0 / longs;

      float x = (float)j / (float)(w - 1);
      float y = (float)i / (float)(h - 1);

      float integer = 0.0;
      float u = modf(x / longDivs, &integer);
      float v = modf(y / latDivs, &integer);

      // checks if this is a grid pixel
      Vector2i gP1 = step(Vector2f(thickness), Vector2f(u, v));
      Vector2i gP2 = step(Vector2f(thickness), Vector2f(1.0 - u, 1.0 - v));

      int result = gP1.x * gP1.y * gP2.x * gP2.y;

      if (result == 0)
      {
        gridlines[(i * w * 3) + (j * 3) + 0] = (unsigned char)(line.x * 255);
        gridlines[(i * w * 3) + (j * 3) + 1] = (unsigned char)(line.y * 255);
        gridlines[(i * w * 3) + (j * 3) + 2] = (unsigned char)(line.z * 255);
      }
      else
      {
        gridlines[(i * w * 3) + (j * 3) + 0] = (unsigned char)(main.x * 255);
        gridlines[(i * w * 3) + (j * 3) + 1] = (unsigned char)(main.y * 255);
        gridlines[(i * w * 3) + (j * 3) + 2] = (unsigned char)(main.z * 255);
      }
    }
  }

  tex->loadTexture2DFromRawData(w, h, gridlines, true, GL_RGB);
  tex->freeData();

  return tex;
}
// Texture *createCheckeredTexture() {}