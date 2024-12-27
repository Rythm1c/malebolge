#include "vec3.h"

/*function definitions for vector operations*/

float dot(const v3D &p1, const v3D &p2) {
  return (p1.x * p2.x) + (p1.y * p2.y) + (p1.z * p2.z);
}
float get_length(const v3D &v) {
  float len_sqrd = pow(v.x, 2.0f) + pow(v.y, 2.0f) + pow(v.z, 2.0f);

  return sqrt(len_sqrd);
}
v3D cross(const v3D &p1, const v3D &p2) {
  return v3D(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z,
             p1.x * p2.y - p1.y * p2.x);
}

v3D normalize(const v3D &v) {

  float constant = 1.0f / get_length(v);

  return v3D(constant * v.x, constant * v.y, constant * v.z);
}
v3D reflect(const v3D &v, const v3D &n) {
  v3D v_new = -2.0f * n * dot(n, v) + v;
  return v_new;
}
v3D clamp(const v3D &v, const v3D &min, const v3D &max) {
  v3D v_new = v;
  v_new.x = clamp(v_new.x, min.x, max.x);
  v_new.y = clamp(v_new.y, min.y, max.y);
  v_new.z = clamp(v_new.z, min.z, max.z);

  return v_new;
}
v3D lerp(v3D a, v3D b, float c) { return (1.0 - c) * a + c * b; }

// miltiplication
v3D operator*(const v3D &l, float r) { return v3D(l.x * r, l.y * r, l.z * r); }
v3D operator*(float r, const v3D &l) { return v3D(l.x * r, l.y * r, l.z * r); }
v3D operator*(const v3D &lhs, const v3D &rhs) {
  return v3D(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}
// division
v3D operator/(const v3D &l, float r) { return v3D(l.x / r, l.y / r, l.z / r); }
// addition
v3D operator+(const v3D &l, const v3D &r) {
  return v3D(l.x + r.x, l.y + r.y, l.z + r.z);
}
// subtraction
v3D operator-(const v3D &l, const v3D &r) {
  return v3D(l.x - r.x, l.y - r.y, l.z - r.z);
}
// comparisons
bool operator==(const v3D &l, const v3D &r) {
  return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}
bool operator!=(const v3D &l, const v3D &r) { return !(l == r); }
