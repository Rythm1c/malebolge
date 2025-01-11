#include "mat2.h"

float Mat2x2::determinant() const
{
  float i = this->xx * this->yy;
  float j = this->xy * this->yx;
  return i - j;
}