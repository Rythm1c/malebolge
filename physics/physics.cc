#include "physics.h"
#include "../math/transform.h"
#include "../headers/engine.h"
#include "../headers/mesh.h"
#include "../shapes/shape.h"
#include <math.h>

// very simple gravity function
// not much going on
void Physics::simpleGravity(v3D &v)
{
    // v = u + at
    // only affects the y component for a simple gravity simulation
    v3D gravity = v3D(0.0, -0.66, 0.0);
    v = v + gravity * Engine::getInstance()->deltaTime;
}
// void friction() {}

// for spherical objects to simulate planet gravitational pulls
// but mostly for particale physics
/* void Physics::gravity(Shape *Pr_mass1, Shape *Pr_mass2)
{
    float grav_factor = 0.01;

    float distance = get_length(Pr_mass1->transform.translation - Pr_mass2->transform.translation );
    // direction from mass1 to mass2
    // |AB| = |AO| + |OB| = |OB| - |AO|
    v3D Obj1_Obj2 = normalize(Pr_mass2->transform.translation  - Pr_mass1->transform.translation );
    // attenuation
    // from grav is proportianl to 1/r^2 but this is to small so 1/2*r
    float mag1 = (1.0 / (distance * 2.0)) * Pr_mass2->g_pull;
    float mag2 = (1.0 / (distance * 2.0)) * Pr_mass1->g_pull;
    // constraint mag to amximum of g_pull
    clamp(mag1, 0.0, Pr_mass2->g_pull);
    clamp(mag2, 0.0, Pr_mass1->g_pull);
    // multiply with factor since result is too large
    v3D grav1 = grav_factor * mag1 * Obj1_Obj2;
    v3D grav2 = grav_factor * mag2 * (Obj1_Obj2 * -1.0);

    Pr_mass1->velocity += grav1;
    Pr_mass2->velocity += grav2;
} */
float Physics::averageSize(Transform obj)
{
    return (obj.scaling.x + obj.scaling.y + obj.scaling.z) / 3.0;
}
AABB Physics::getAABB(const v3D &pos, const v3D &size)
{
    float xmin = pos.x - size.x;
    float xmax = pos.x + size.x;
    float ymin = pos.y - size.y;
    float ymax = pos.y + size.y;
    float zmin = pos.z - size.z;
    float zmax = pos.z + size.z;

    return AABB{v3D(xmin, ymin, zmin), v3D(xmax, ymax, zmax)};
}
void Physics::cSphereVsSphere(Shape *Pr_sphere1, Shape *Pr_sphere2)
{

    v3D pos1 = Pr_sphere1->transform.translation;
    v3D pos2 = Pr_sphere2->transform.translation;
    // smaller distance between sphere centers than sum of both sphere magnitudes
    // indicates a collision has occuered between them

    // distance between spheres
    float distance = get_length(pos1 - pos2);
    // total magnitude of both spheres
    float mag1 = averageSize(Pr_sphere1->transform);
    float mag2 = averageSize(Pr_sphere2->transform);
    float totalMagnitudes = mag1 + mag2;
    // is distance smaller than total mag

    // work inprogress
    // does not conserve momentum
    if (distance <= totalMagnitudes)
    {
        // |AB| = |AO| + |OB| = |OB| - |AO|
        v3D normal = normalize(pos2 - pos1);
        // update position to remove them form each others bounding volumes
        Pr_sphere1->transform.translation = pos2 + totalMagnitudes * -1.0 * normal;
        Pr_sphere2->transform.translation = pos1 + totalMagnitudes * 1.0 * normal;
        // reflect velocities around respective normals
        v3D v1 = reflect(Pr_sphere1->velocity, -1.0 * normal);
        v3D v2 = reflect(Pr_sphere2->velocity, 1.0 * normal);
        // reduce velocities based on angle of contact with normal
        v1 = v1 * dot(normalize(v1), -1.0 * normal);
        v2 = v2 * dot(normalize(v2), 1.0 * normal);
        // finally update velocities
        Pr_sphere1->velocity = 0.8f * v1;
        Pr_sphere2->velocity = 0.8f * v2;
    }
}
// func to resolve aabb-aabb collisions
// very primitive and simple for now  not very sophisticated
void Physics::cAABBVsAABB(Shape *pr_obj1, Shape *pr_obj2)
{
    const AABB obj1 = getAABB((*pr_obj1).transform.translation, (*pr_obj1).transform.scaling);
    const AABB obj2 = getAABB((*pr_obj2).transform.translation, (*pr_obj2).transform.scaling);

    bool xintersect = (obj1.min.x <= obj2.max.x) && (obj1.max.x >= obj2.min.x);
    bool yintersect = (obj1.min.y <= obj2.max.y) && (obj1.max.y >= obj2.min.y);
    bool zintersect = (obj1.min.z <= obj2.max.z) && (obj1.max.z >= obj2.min.z);

    if (xintersect && yintersect && zintersect)
    {
        v3D nPos = v3D(0.0);
        v3D nVelocity = v3D(0.0);
        v3D normal = v3D(0.0);

        // get displacemets for each axis
        float dx1 = obj1.min.x - obj2.max.x;
        float dx2 = obj1.max.x - obj2.min.x;
        float dy1 = obj1.min.y - obj2.max.y;
        float dy2 = obj1.max.y - obj2.min.y;
        float dz1 = obj1.min.z - obj2.max.z;
        float dz2 = obj1.max.z - obj2.min.z;

        float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
        float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
        float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

        // gets the smallest instesection per axis
        // and updates the appropriate axis with the displacement
        if (abs(dx) < abs(dy) && abs(dx) < abs(dz))
        {
            normal = normalize(v3D(-dx, 0.0, 0.0));
            nPos = pr_obj1->transform.translation + v3D(-dx, 0.0, 0.0);
        }
        else if (abs(dy) < abs(dx) && abs(dy) < abs(dz))
        {
            normal = normalize(v3D(0.0, -dy, 0.0));
            nPos = pr_obj1->transform.translation + v3D(0.0, -dy, 0.0);
        }
        else
        {
            normal = normalize(v3D(0.0, 0.0, -dz));
            nPos = pr_obj1->transform.translation + v3D(0.0, 0.0, -dz);
        }

        nVelocity = reflect(pr_obj1->velocity * 0.7, normal);

        pr_obj1->transform.translation = nPos;
        pr_obj1->velocity = nVelocity;
    }
}

void Physics::cSphereVsAABB(Shape *pr_sphere, Shape *pr_aabb)
{

    v3D sPos = pr_sphere->transform.translation;
    v3D aabbPos = pr_aabb->transform.translation;
    v3D sScale = pr_sphere->transform.scaling;
    v3D aabbScale = pr_aabb->transform.scaling;

    float radius = averageSize(pr_sphere->transform);
    // BA=AO+BO=-OB+OA
    v3D difference = sPos - aabbPos;
    v3D clamped = clamp(difference, -1.0 * aabbScale, aabbScale);
    v3D closestPoint = clamped + aabbPos;

    float distance = get_length(sPos - closestPoint);

    if (distance <= radius)
    {
        // BA=BO+OA=OA-OB
        v3D diff = pr_sphere->transform.translation - closestPoint;
        v3D normal = normalize(diff);
        pr_sphere->transform.translation += normal * averageSize(pr_sphere->transform) - diff;
        pr_sphere->velocity = 0.8 * reflect(pr_sphere->velocity, normal);
    }
}
