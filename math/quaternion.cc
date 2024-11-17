//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// home made quaternion math lib cause i have a big ego.
// "john vince - quaternions for for computer graphics" was a massive help along with
// "gabor szauer - hands on c++ game animation programming packt", both great books.

#include "quaternion.h"
#include "vec3.h"
#include "mat4.h"

Quat::Quat(float angle, v3D axis)
{
    float s = std::sin(to_radians(angle / 2.0));
    float c = std::cos(to_radians(angle / 2.0));

    v3D unit = normalize(axis);

    this->s = c;
    this->x = unit.x * s;
    this->y = unit.y * s;
    this->z = unit.z * s;
}

float Quat::norm()
{
    float x2 = std::pow(x, 2.0);
    float y2 = std::pow(y, 2.0);
    float z2 = std::pow(z, 2.0);
    float s2 = std::pow(s, 2.0);

    return std::sqrt(x2 + y2 + z2 + s2);
}

Quat Quat::unit()
{
    float coeff = 1.0 / this->norm();

    return Quat(
        x * coeff,
        y * coeff,
        z * coeff,
        s * coeff);
}

Quat Quat::conjugate()
{
    return Quat(-x, -y, -z, s);
}

Quat Quat::inverse()
{
    float lenSqrd = x * x + y * y + z * z + s * s;
    float invLen = 1.0 / lenSqrd;

    return this->conjugate() * invLen;
}

float dot(Quat &lhs, Quat &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.s * rhs.s;
}

v3D axis(Quat q) { return v3D(q.x, q.y, q.z); }

Quat mix(Quat from, Quat to, float t)
{
    return (1.0 - t) * from + t * to;
}

mat4x4 Quat::toMat()
{
    mat4x4 result = mat4x4();

    float x2 = std::pow(x, 2.0);
    float y2 = std::pow(y, 2.0);
    float z2 = std::pow(z, 2.0);
    // first row
    result.xx = 1.0 - 2.0 * (y2 + z2);
    result.xy = 2.0 * (x * y - s * z);
    result.xz = 2.0 * (x * z + s * y);
    // second row
    result.yx = 2.0 * (x * y + s * z);
    result.yy = 1.0 - 2.0 * (x2 + z2);
    result.yz = 2.0 * (y * z - s * x);
    // third row
    result.zx = 2.0 * (x * z - s * y);
    result.zy = 2.0 * (y * z + s * x);
    result.zz = 1.0 - 2.0 * (x2 + y2);

    result.ww = 1.0;

    return result;
}
// operator overloads
//________________________________________________________________________
//________________________________________________________________________

Quat operator+(const Quat &lhs, const Quat &rhs)
{
    return Quat(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.s + rhs.s);
}

Quat operator*(float lhs, const Quat &rhs)
{
    return Quat(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.s);
}
Quat operator*(const Quat lhs, float &rhs) { return rhs * lhs; }

v3D operator*(const Quat &lhs, const v3D &rhs)
{
    v3D a = axis(lhs) * 2.0 * dot(axis(lhs), rhs);
    v3D b = rhs * (lhs.s * lhs.s - dot(axis(lhs), axis(lhs)));
    v3D c = cross(axis(lhs), rhs) * 2.0 * lhs.s;

    return a + b + c;
}

v3D operator*(v3D &lhs, Quat &rhs) { return rhs * lhs; }

Quat operator*(const Quat &lhs, const Quat &rhs)
{
    Quat result = Quat(0.0);

    result.x = lhs.s * rhs.x + lhs.x * rhs.s + lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.s * rhs.y + lhs.y * rhs.s + lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = lhs.s * rhs.z + lhs.z * rhs.s + lhs.x * rhs.y - lhs.y * rhs.x;
    result.s = lhs.s * rhs.s - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;

    return result;
}