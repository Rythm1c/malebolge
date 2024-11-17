#include "vec2.h"

bool operator==(const v2D &l, const v2D &r)
{
    return (l.x == r.x) && (l.y == r.y);
}
