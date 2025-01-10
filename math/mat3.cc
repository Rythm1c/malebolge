#include "mat3.h"

Mat3x3 transpose(const Mat3x3 &m)
{
  return Mat3x3(
      m.xx, m.yx, m.zx,
      m.xy, m.yy, m.zy,
      m.xz, m.yz, m.zz);
}

Mat3x3 operator+(const Mat3x3 &l, float r)
{

  return Mat3x3(
      l.rows[0] + r,
      l.rows[1] + r,
      l.rows[2] + r);
}

Mat3x3 operator-(const Mat3x3 &l, float r)
{

  return Mat3x3(
      l.rows[0] - r,
      l.rows[1] - r,
      l.rows[2] - r);
}

Mat3x3 operator*(const Mat3x3 &l, float r)
{

  return Mat3x3(
      l.rows[0] * r,
      l.rows[1] * r,
      l.rows[2] * r);
}
Mat3x3 operator*(float l, const Mat3x3 &r) { return r * l; }

Mat3x3 operator/(const Mat3x3 &l, float r)
{

  return Mat3x3(
      l.rows[0] / r,
      l.rows[1] / r,
      l.rows[2] / r);
}

Vector3f operator*(const Mat3x3 &l, const Vector3f &r)
{
  return Vector3f(
      dot(l.rows[0], r),
      dot(l.rows[1], r),
      dot(l.rows[2], r));
}

Mat3x3 operator+(const Mat3x3 &l, const Mat3x3 &r)
{
  return Mat3x3(
      l.rows[0] + r.rows[0],
      l.rows[1] + r.rows[1],
      l.rows[2] + r.rows[2]);
}

Mat3x3 operator-(const Mat3x3 &l, const Mat3x3 &r)
{
  return Mat3x3(
      l.rows[0] - r.rows[0],
      l.rows[1] - r.rows[1],
      l.rows[2] - r.rows[3]);
}

Mat3x3 operator*(const Mat3x3 &l, const Mat3x3 &r)
{

  return Mat3x3(
      M3D(0, 0), M3D(0, 1), M3D(0, 2), //
      M3D(1, 0), M3D(1, 1), M3D(1, 2), //
      M3D(2, 0), M3D(2, 1), M3D(2, 2));
}