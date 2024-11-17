#include "track.h"

namespace TrackHelpers
{
    inline float interpolate(float a, float b, float c)
    {
        return (1.0 - c) * a + c * b;
    }
    inline v3D interpolate(const v3D &a, const v3D &b, float c)
    {
        return lerp(a, b, c);
    }
    inline Quat interpolate(Quat &a, Quat &b, float c)
    {
        Quat result = mix(a, b, c);

        if (dot(a, b) < 0.0)
        {
            result = mix(a, -1.0 * b, c);
        }

        return result.unit();
    }

    inline float AdjustHermiteResult(float f)
    {
        return f;
    }
    inline v3D AdjustHermiteResult(const v3D &v)
    {
        return v;
    }
    inline Quat AdjustHermiteResult(Quat &q)
    {
        return q.unit();
    }

    inline void Neighborhood(const float &a, float &b) {}
    inline void Neighborhood(const v3D &a, v3D &b) {}
    inline void Neighborhood(Quat &a, Quat &b)
    {
        if (dot(a, b) < 0)
        {
            b = -1.0 * b;
        }
    }
};

template <typename T, size_t N>
float Track<T, N>::getStartTime()
{
    return frames[0].time;
}

template <typename T, size_t N>
float Track<T, N>::getEndTime()
{
    return frames[frames.size() - 1].time;
}