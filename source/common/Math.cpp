#include "Math.h"

#include <tgmath.h>

float DegreesToRadians(float degrees)
{
    return degrees * M_PI / 180;
}

float RadiansToDegrees(float radians)
{
    return radians * 180 / M_PI;
}

int NormalizeAngle(int degree_angle)
{
    if (degree_angle < 0) return 360 - (std::abs(degree_angle) % 360);
    else if (degree_angle >= 360) return degree_angle % 360;

    return degree_angle;
}

Vector2 PolarToCartesian(float radius, float degree_angle)
{
    float rad_angle = DegreesToRadians(degree_angle);

    return {radius * std::cos(rad_angle), radius * std::sin(rad_angle)};
}

Vector2 CartesianToPolar(float x, float y)
{
    // Pythagoras' theorum lol.
    float r = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

    float rad_angle;
    if (y == 0) rad_angle = 0;
    if (x == 0) rad_angle = DegreesToRadians(90);
    else rad_angle = ::atan2(y, x);

    return {r, RadiansToDegrees(rad_angle)};
}

std::vector<double> linspace(double start, double end, int num_points)
{
    std::vector<double> linspaced{};

    if (num_points <= 0) { return linspaced; }
    if (num_points == 1) 
    {
        linspaced.push_back(start);
        return linspaced;
    }

    double delta = (end - start) / (num_points - 1);

    for(int index=0; index < num_points - 1; ++index)
    {
        linspaced.push_back(start + delta * index);
    }

    linspaced.push_back(end);
    return linspaced;
}
