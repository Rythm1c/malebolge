#include "transform.h"

mat4x4 Transform::get()
{
    v3D x = orientation * v3D(1.0, 0.0, 0.0);
    v3D y = orientation * v3D(0.0, 1.0, 0.0);
    v3D z = orientation * v3D(0.0, 0.0, 1.0);

    x = x * scaling.x;
    y = y * scaling.y;
    z = z * scaling.z;

    v3D p = translation;

    return mat4x4(
        x.x, y.x, z.x, p.x, //
        x.y, y.y, z.y, p.y, //
        x.z, y.z, z.z, p.z, //
        0.0, 0.0, 0.0, 1.0  //
    );
}

Transform Transform::inverse()
{
    Transform inv = Transform();

    inv.orientation = orientation.inverse();

    inv.scaling.x = 1.0 / scaling.x;
    inv.scaling.y = 1.0 / scaling.y;
    inv.scaling.z = 1.0 / scaling.z;

    v3D inv_trans = -1.0 * translation;
    inv.translation = inv.orientation * (inv.scaling * inv_trans);

    return inv;
}

Transform combine(const Transform &t1, const Transform &t2)
{
    Transform result = Transform();

    result.scaling = t1.scaling * t2.scaling;

    result.orientation = t1.orientation * t2.orientation;
    // mhhhh have no idea what this is
    result.translation = t1.orientation * (t1.scaling * t2.translation);

    result.translation = t1.translation + result.translation;

    return result;
}
Transform transformFromMat(mat4x4 &mat)
{
    Transform transform = Transform();

    v3D translation = v3D(
        mat.xw,
        mat.yw,
        mat.zw);

    Quat orientation = mat.toQuat();
    // Quat d = &mat.data;
    mat4x4 rot_scale_mat = mat4x4(
        mat.xx, mat.xy, mat.xz, 0.0, //
        mat.yx, mat.yy, mat.yz, 0.0, //
        mat.zx, mat.zy, mat.zz, 0.0, //
        0.0, 0.0, 0.0, 1.0);

    mat4x4 inv_rot_mat = orientation.inverse().toMat();
    mat4x4 scale_skew_mat = rot_scale_mat * inv_rot_mat;

    v3D scaling = v3D(
        scale_skew_mat.xx,
        scale_skew_mat.yy,
        scale_skew_mat.zz);

    transform.translation = translation;
    transform.orientation = orientation;
    transform.scaling = scaling;

    return transform;
}