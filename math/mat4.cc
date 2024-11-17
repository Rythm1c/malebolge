#include "mat4.h"

mat4x4 translate(const v3D t)
{
    mat4x4 trans;
    trans.xw = t.x;
    trans.yw = t.y;
    trans.zw = t.z;
    return trans;
}
mat4x4 scale(const v3D s)
{
    mat4x4 trans;
    trans.xx = s.x;
    trans.yy = s.y;
    trans.zz = s.z;
    return trans;
}
mat4x4 rotationX(float angle)
{
    mat4x4 trans;
    trans.xx = 1.0f;
    trans.yy = cos(to_radians(angle));
    trans.yz = -sin(to_radians(angle));
    trans.zy = sin(to_radians(angle));
    trans.zz = cos(to_radians(angle));
    trans.ww = 1.0f;
    return trans;
}
mat4x4 rotationY(float angle)
{
    mat4x4 trans;
    trans.xx = cos(to_radians(angle));
    trans.xz = sin(to_radians(angle));
    trans.yy = 1.0f;
    trans.zx = -sin(to_radians(angle));
    trans.zz = cos(to_radians(angle));
    trans.ww = 1.0f;
    return trans;
}
mat4x4 rotationZ(float angle)
{
    mat4x4 trans;
    trans.xx = cos(to_radians(angle));
    trans.xy = sin(to_radians(angle));
    trans.yx = -sin(to_radians(angle));
    trans.yy = cos(to_radians(angle));
    trans.zz = 1.0f;
    trans.ww = 1.0f;
    return trans;
}
mat4x4 look_at(const v3D &pos, const v3D &fr, const v3D &up)
{
    // cr =cemra right vector
    v3D cd = normalize(pos - fr);
    v3D cr = normalize(cross(up, cd));
    v3D cu = normalize(cross(cd, cr));

    mat4x4 mat;
    // rotation and translatio matrix combined
    mat.rs[0][0] = cr.x, mat.rs[0][1] = cr.y, mat.rs[0][2] = cr.z;
    mat.rs[0][3] = -pos.x * cr.x - pos.y * cr.y - pos.z * cr.z;

    mat.rs[1][0] = cu.x, mat.rs[1][1] = cu.y, mat.rs[1][2] = cu.z;
    mat.rs[1][3] = -pos.x * cu.x - pos.y * cu.y - pos.z * cu.z;

    mat.rs[2][0] = cd.x, mat.rs[2][1] = cd.y, mat.rs[2][2] = cd.z;
    mat.rs[2][3] = -pos.x * cd.x - pos.y * cd.y - pos.z * cd.z;

    mat.rs[3][0] = 0.0f, mat.rs[3][1] = 0.0f, mat.rs[3][2] = 0.0f;
    mat.rs[3][3] = 1.0f;

    return mat;
}
mat4x4 orthogonal(float l, float r, float b, float t, float n, float f)
{
    mat4x4 proj;
    proj.xx = 2.0f / (r - l);
    proj.xw = -((r + l) / (r - l));
    proj.yy = 2.0f / (t - b);
    proj.yw = -((t + b) / (t - b));
    proj.zz = -2.0f / (f - n);
    proj.zw = -((f + n) / (f - n));
    proj.ww = 1.0f;

    return proj;
}

mat4x4 frustrum(float l, float r, float b, float t, float n, float f)
{
    mat4x4 proj;
    proj.xx = (2.0f * n) / (r - l);
    proj.xz = (r + l) / (r - l);
    proj.yy = (2.0f * n) / (t - b);
    proj.yz = (t + b) / (t - b);
    proj.zz = -(f + n) / (f - n);
    proj.zw = (-2.0f * f * n) / (f - n);
    proj.wz = -1.0f;
    proj.ww = 0.0f;
    return proj;
}

mat4x4 perspective(float fov, float aspectRatio, float N, float F)
{

    float ymax = N * tan((to_radians(fov / 2.0f)));
    float xmax = ymax * aspectRatio;

    return frustrum(-xmax, xmax, -ymax, ymax, N, F);
}
mat4x4 operator*(const mat4x4 &l, float r)
{
    return mat4x4(
        l.xx * r, l.xy * r, l.xz * r, l.xw * r,
        l.yx * r, l.yy * r, l.yz * r, l.yw * r,
        l.zx * r, l.zy * r, l.zz * r, l.zw * r,
        l.wx * r, l.wy * r, l.wz * r, l.ww * r);
}
mat4x4 operator*(float l, const mat4x4 &r)
{
    return mat4x4(
        r.xx * l, r.xy * l, r.xz * l, r.xw * l,
        r.yx * l, r.yy * l, r.yz * l, r.yw * l,
        r.zx * l, r.zy * l, r.zz * l, r.zw * l,
        r.wx * l, r.wy * l, r.wz * l, r.ww * l);
}
v4D operator*(const mat4x4 &m, const v4D &v)
{
    return v4D(
        M4V4D(0, v.x, v.y, v.z, v.w),
        M4V4D(1, v.x, v.y, v.z, v.w),
        M4V4D(2, v.x, v.y, v.z, v.w),
        M4V4D(3, v.x, v.y, v.z, v.w));
}
mat4x4 operator*(const mat4x4 &l, const mat4x4 &r)
{
    return mat4x4(
        M4D(0, 0), M4D(0, 1), M4D(0, 2), M4D(0, 3),
        M4D(1, 0), M4D(1, 1), M4D(1, 2), M4D(1, 3),
        M4D(2, 0), M4D(2, 1), M4D(2, 2), M4D(2, 3),
        M4D(3, 0), M4D(3, 1), M4D(3, 2), M4D(3, 3));
}
mat4x4 operator/(const mat4x4 &l, float r)
{
    return mat4x4(
        l.xx / r, l.xy / r, l.xz / r, l.xw / r,
        l.yx / r, l.yy / r, l.yz / r, l.yw / r,
        l.zx / r, l.zy / r, l.zz / r, l.zw / r,
        l.wx / r, l.wy / r, l.wz / r, l.ww / r);
}
mat4x4 operator+(const mat4x4 &l, const mat4x4 &r)
{
    return mat4x4(
        l.xx + r.xx, l.xy + r.xy, l.xz + r.xz, l.xw + r.xw,
        l.yx + r.yx, l.yy + r.yy, l.yz + r.yz, l.yw + r.yw,
        l.zx + r.zx, l.zy + r.zy, l.zz + r.zz, l.zw + r.zw,
        l.wx + r.wx, l.wy + r.wy, l.wz + r.wz, l.ww + r.ww);
}
mat4x4 operator-(const mat4x4 &l, const mat4x4 &r)
{
    return mat4x4(
        l.xx - r.xx, l.xy - r.xy, l.xz - r.xz, l.xw - r.xw,
        l.yx - r.yx, l.yy - r.yy, l.yz - r.yz, l.yw - r.yw,
        l.zx - r.zx, l.zy - r.zy, l.zz - r.zz, l.zw - r.zw,
        l.wx - r.wx, l.wy - r.wy, l.wz - r.wz, l.ww - r.ww);
}
bool operator==(const mat4x4 &l, const mat4x4 &r)
{
    for (int i = 0; i < 16; i++)
    {
        if (l.fv[i] != r.fv[i])
        {
            return false;
        }
    }

    return true;
}
bool operator!=(const mat4x4 &l, const mat4x4 &r)
{
    return !(l == r);
}