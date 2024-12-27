#ifndef FRAME_H
#define FRAME_H

#include <iostream>

template <size_t N> struct Frame {
  float m_value[N];
  float m_in[N];
  float m_out[N];
  float time;
};

enum Interpolation {
  Constant,
  Linear,
  Cubic,
};

#endif
