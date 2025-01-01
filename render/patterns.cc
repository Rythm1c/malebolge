#include "patterns.h"
#include "texture.h"
#include "../math/math.h"

Texture *createGridTexture(
    int w, int h, Color3f main, Color3f line,
    int lats, int longs, int thickness)
{
  unsigned char *gridlines = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

  Texture *tex = new Texture();

  int latDivs = h / lats;
  int longDivs = w / longs;

  // 1.0 => 255 => ff
  for (int i = 0; i < h; i++)
  {
    int y = i % latDivs;
    bool vertical = y == 0;

    for (int j = 0; j < w; j++)
    {

      int x = j % longDivs;
      bool horizontal = x == 0;
      bool result = vertical || horizontal;

      unsigned char col[3] = {0, 0, 0};

      if (result)
      {
        col[0] = line.x * 255;
        col[1] = line.y * 255;
        col[2] = line.z * 255;
      }
      else
      {
        col[0] = main.x * 255;
        col[1] = main.y * 255;
        col[2] = main.z * 255;
      }

      gridlines[(i * w * 3) + (j * 3) + 0] = col[0];
      gridlines[(i * w * 3) + (j * 3) + 1] = col[1];
      gridlines[(i * w * 3) + (j * 3) + 2] = col[2];
    }
  }

  tex->loadTexture2DFromRawData(w, h, gridlines, false, GL_RGB, GL_NEAREST);
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
        col[0] = first.x * 255;
        col[1] = first.y * 255;
        col[2] = first.z * 255;
      }
      else
      {
        col[0] = second.x * 255;
        col[1] = second.y * 255;
        col[2] = second.z * 255;
      }

      checkers[(i * w * 3) + (j * 3) + 0] = col[0];
      checkers[(i * w * 3) + (j * 3) + 1] = col[1];
      checkers[(i * w * 3) + (j * 3) + 2] = col[2];
    }
  }

  Texture *tex = new Texture();
  tex->loadTexture2DFromRawData(w, h, checkers, false, GL_RGB, GL_NEAREST);
  tex->freeData();

  return tex;
}