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