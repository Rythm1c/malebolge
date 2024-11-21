#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <vector>
#include "frame.h"
#include "../math/vec3.h"
#include "../math/quaternion.h"

/// @brief holds the animation for a single skeleton joint
/// @tparam N track type (1=scalar track, 3=vector track, 4=quaternion track)
template <typename T, size_t N>
class Track
{
public:
    Track() : interpolation(Linear) {}
    ~Track() {}

    std::vector<Frame<N>> frames;
    Interpolation interpolation;

    unsigned int size();

    float getStartTime();
    float getEndTime();

    T sample(float time, bool looping);
    T sampleConst(float time, bool looping);
    T sampleLinear(float time, bool looping);
    T sampleCubic(float time, bool looping);

    size_t frameIndex(float time, bool looping);
    float adjustToFitTrack(float time, bool looping);
    T hermite(float time, const T &p1, const T &s1, const T &p2, const T &s2);

    T cast(float *value);
};

typedef Track<float, 1> SCalarTrack;
typedef Track<v3D, 3> VectorTrack;
typedef Track<Quat, 4> QuatTrack;

#endif