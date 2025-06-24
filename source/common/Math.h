#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include "Vector2.h"
#include <type_traits>

// Angles.
float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);

// Correctly convert negative degrees and if degrees are over 360, modulo.
int NormalizeAngle(int degree_angle);

// Coordinates.
Vector2 PolarToCartesian(float radius, float degree_angle);
Vector2 CartesianToPolar(float x, float y);

// Like np.linspace
std::vector<double> linspace(double start, double end, int num_points);

// Round value to the nearest larger (or equal) multiple of multiplier.
template <std::integral T>
T ceil_to_multiple(T value, T multiplier)
{
    if (value % multiplier == 0)
    {
        return value;
    }

    return value + multiplier - (value % multiplier);
}

template <typename T> 
concept number = std::is_integral<T>::value || std::is_floating_point<T>::value;

template <number T>
T clamp(T start, T end, T value)
{
    if (value < start) return start;
    if (value > end) return end;

    return value;
}

template <number T>
T linear_interpolate(T start, T end, float fraction)
{
    // TODO: There must be a more efficient implementation.
    fraction = clamp<float>(0, 1, fraction);
    if (end < start)
    {
        T temp = start;
        start = end;
        end = temp;

        fraction = 1.0f - fraction;
    }

    return start + static_cast<T>((end - start) * fraction);
}

#endif // COMMON_MATH_H