#include "textures.h"
#include "texture.h"
#include "../math/math.h"
#include <string.h>

Texture *createGridTexture(
    int w, int h, Color3f main, Color3f line,
    int lats, int longs, float thickness)
{
  unsigned char *gridlines = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));
  //memset(gridlines, 0, sizeof(char) * 3 * w * h);

  Texture *tex = new Texture();

  float latDivs = 1.0 / float(lats);
  float longDivs = 1.0 / float(longs);

  std::cout << fract(5.99 / 2.0) << std::endl;

  // 1.0 => 255 => ff
  for (int i = 0; i < h; i++)
  {
    float y = (float)i / float(h - 1);
    float v = fract(y / latDivs);

    for (int j = 0; j < w; j++)
    {

      float x = (float)j / float(w - 1);
      float u = fract(x / longDivs);

      Vector2f edge = Vector2f(thickness);
      // checks if this is a grid pixel

      int a = step(thickness, u);
      int b = step(thickness, v);
      int c = step(thickness, 1.0 - u);
      int d = step(thickness, 1.0 - v);

      int result = a * b * c * d;

      unsigned char col[3] = {0, 0, 0};

      if (result == 0)
      {
        col[0] = (unsigned char)(line.x * 255);
        col[1] = (unsigned char)(line.y * 255);
        col[2] = (unsigned char)(line.z * 255);
      }
      else
      {
        col[0] = (unsigned char)(main.x * 255);
        col[1] = (unsigned char)(main.y * 255);
        col[2] = (unsigned char)(main.z * 255);
      }

      gridlines[(i * w * 3) + (j * 3) + 0] = col[0];
      gridlines[(i * w * 3) + (j * 3) + 1] = col[1];
      gridlines[(i * w * 3) + (j * 3) + 2] = col[2];
    }
  }

  tex->loadTexture2DFromRawData(w, h, gridlines, true, GL_RGB);
  tex->freeData();

  return tex;
}
Texture *createCheckeredTexture(
    int w, int h, Color3f first, Color3f second, int divs)
{

  unsigned char *checkers = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

  float square = 2.0 / float(divs);

  for (int i = 0; i < h; i++)
  {
    float y = (float)i / float(h - 1);
    float v = fract(y / square);

    for (int j = 0; j < w; j++)
    {
      float x = (float)j / float(w - 1);
      float u = fract(x / square);

      int a = step(0.5, u);
      int b = step(0.5, v);

      int result = (a + b) % 2;
      unsigned char col[3] = {0, 0, 0};

      if (result == 0)
      {
        col[0] = (unsigned char)(first.x * 255);
        col[1] = (unsigned char)(first.y * 255);
        col[2] = (unsigned char)(first.z * 255);
      }
      else
      {
        col[0] = (unsigned char)(second.x * 255);
        col[1] = (unsigned char)(second.y * 255);
        col[2] = (unsigned char)(second.z * 255);
      }

      checkers[(i * w * 3) + (j * 3) + 0] = col[0];
      checkers[(i * w * 3) + (j * 3) + 1] = col[1];
      checkers[(i * w * 3) + (j * 3) + 2] = col[2];
    }
  }

  Texture *tex = new Texture();
  tex->loadTexture2DFromRawData(w, h, checkers, true, GL_RGB);
  tex->freeData();

  return tex;
}