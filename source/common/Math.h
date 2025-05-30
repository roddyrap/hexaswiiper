#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include "Vector2.h"

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

#endif // COMMON_MATH_H