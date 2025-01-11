#ifndef MATRIX2x2_H
#define MATRIX2x2_h

#include "vec2.h"

struct Mat2x2
{
  union
  {
    struct
    {
      float xx;
      float xy;
      float yx;
      float yy;
    };

    float rc[2][2];

    Vector2f rows[2];
  };
};

#endif