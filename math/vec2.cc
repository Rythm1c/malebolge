#include "vec2.h"

Vector2i step(Vector2f a, Vector2f b)
{
  return Vector2i((int)step(a.x, b.x), (int)step(a.y, b.y));
}

bool operator==(const Vector2f &l, const Vector2f &r)
{
  return (l.x == r.x) && (l.y == r.y);
}
