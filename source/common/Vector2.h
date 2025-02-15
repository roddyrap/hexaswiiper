#ifndef COMMON_VECTOR2_H
#define COMMON_VECTOR2_H

#include <type_traits>

// For std::hash
#include <functional>

template <typename T>
concept Numeric = std::is_integral<T>::value || std::is_floating_point<T>::value;

template <Numeric NumberType>
struct Vector2Base
{
    Vector2Base() : x{}, y{} {}
    explicit Vector2Base(NumberType x) : x{x} {}
    Vector2Base(NumberType x, NumberType y) : x{x}, y{y} {};

    bool operator==(const Vector2Base<NumberType>& other) const
    {
        return x == other.x && y == other.y;
    }

    NumberType x;
    NumberType y;
};

template <Numeric NumberType>
struct std::hash<Vector2Base<NumberType>>
{
    std::size_t operator()(const Vector2Base<NumberType>& vector2) const
    {
        // Cantor pairing function.
        return (vector2.x + vector2.y) * (vector2.x + vector2.y + 1) / 2 + vector2.x;
    }
};


using Vector2 = Vector2Base<float>;
using Vector2Int = Vector2Base<int>;

#endif // COMMON_VECTOR2_H