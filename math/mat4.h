#ifndef MAT4X4_HPP
#define MAT4X4_HPP

#include "math.h"
#include "vec3.h"
#include "vec4.h"

// for multiplication of mat4x4s and vec4s
#define M4V4D(mRow, x, y, z, w) \
        x *m.fv[mRow * 4 + 0] + \
        y *m.fv[mRow * 4 + 1] + \
        z *m.fv[mRow * 4 + 2] + \
        w *m.fv[mRow * 4 + 3]

// for multiplication of two 4x4 mats
#define M4D(aRow, bCol)                           \
        l.fv[0 + 4 * aRow] * r.fv[bCol + 4 * 0] + \
        l.fv[1 + 4 * aRow] * r.fv[bCol + 4 * 1] + \
        l.fv[2 + 4 * aRow] * r.fv[bCol + 4 * 2] + \
        l.fv[3 + 4 * aRow] * r.fv[bCol + 4 * 3]


    struct mat4x4
    {
        union
        {
             struct
             {
                //        column 1  column 2  column 3  column 4
                /*row 1*/ float xx; float xy; float xz; float xw;
                /*row 2*/ float yx; float yy; float yz; float yw;
                /*row 3*/ float zx; float zy; float zz; float zw;
                /*row 4*/ float wx; float wy; float wz; float ww;
             };
            float rs[4][4];
            std::array<float, 16> fv;
         };
        // default constructor
        // set identity matrix
         mat4x4()
            : xx(1.0f), xy(0.0f), xz(0.0f), xw(0.0f),
              yx(0.0f), yy(1.0f), yz(0.0f), yw(0.0f),
              zx(0.0f), zy(0.0f), zz(1.0f), zw(0.0f),
              wx(0.0f), wy(0.0f), wz(0.0f), ww(1.0f)
        {
        }
        // constract matrix using an array
        mat4x4(float *fv)
            : xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
              yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
              zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
              wx(fv[12]), wy(fv[13]), wz(fv[14]), ww(fv[15])
        {
        }

        mat4x4(
            float _00, float _01, float _02, float _03,
            float _10, float _11, float _12, float _13,
            float _20, float _21, float _22, float _23,
            float _30, float _31, float _32, float _33)
            : xx(_00), xy(_01), xz(_02), xw(_03),
              yx(_10), yy(_11), yz(_12), yw(_13),
              zx(_20), zy(_21), zz(_22), zw(_23),
              wx(_30), wy(_31), wz(_32), ww(_33)
        {
        }

        struct Quat toQuat();
    };
    // create a translation matrix out of a vec3
    // t : translation vector
    mat4x4 translate(const v3D t);
    // create a scaling matrix out of a vec3
    // s : scaling vector
    mat4x4 scale(const v3D s);
    // create a rotation matrix for the X axis
    // angle : rotational angle
    mat4x4 rotationX(float angle);
    // create a rotation matrix for the Y axis
    // angle : rotational angle
    mat4x4 rotationY(float angle);
    // create a rotation matrix for the Z axis
    // angle : rotational angle
    mat4x4 rotationZ(float angle);
    // create a view matrix
    mat4x4 look_at(const v3D &pos, const v3D &dir, const v3D &up);
    // for creating an orthogonal projection matrix
    mat4x4 orthogonal(float l, float r, float b, float t, float n = -1.0f, float f = 1.0f);
    // for creating a perspective projection
    // N, F = near and far plane respectively
    mat4x4 perspective(float fov, float aspectRation, float N, float F);
    mat4x4 frustrum(float l, float r, float t, float b, float n, float f);



// multiplication operations
mat4x4 operator*(const mat4x4 &l, float r);
mat4x4 operator*(float l, const mat4x4 &r);
mat4x4 operator*(const mat4x4 &l, const mat4x4 &r);
v4D operator*(const mat4x4 &m, const v4D &v);
// division operations
mat4x4 operator/(const mat4x4 &l, float r);
// addition operations
mat4x4 operator+(const mat4x4 &l, const mat4x4 &r);
// sutraction operations
mat4x4 operator-(const mat4x4 &l, const mat4x4 &r);
// comparison operations
bool operator==(const mat4x4 &m1, const mat4x4 &m2);
bool operator!=(const mat4x4 &m1, const mat4x4 &m2);

#endif