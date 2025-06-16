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
    Vector2Base(NumberType x, NumberType y) : x{x}, y{y} {}

    bool operator==(const Vector2Base<NumberType>& other) const
    {
        return x == other.x && y == other.y;
    }

    Vector2Base<NumberType> operator-() const
    {
        return Vector2Base<NumberType>{-this->x, -this->y};
    }


    template<Numeric MulType>
    friend Vector2Base<NumberType> operator*(Vector2Base<NumberType> lhs, const MulType& rhs)
    {
        lhs.x *= rhs;
        lhs.y *= rhs;
        return lhs;
    }

    template<Numeric MinusType>
    friend Vector2Base<NumberType> operator-(Vector2Base<NumberType> lhs, const MinusType& rhs)
    {
        lhs.x -= rhs;
        lhs.y -= rhs;
        return lhs;
    }

    template<Numeric PlusType>
    friend Vector2Base<NumberType> operator+(Vector2Base<NumberType> lhs, const PlusType& rhs)
    {
        lhs.x += rhs;
        lhs.y += rhs;
        return lhs;
    }

    // x * x, y * y
    Vector2Base<NumberType> operator*(const Vector2Base<NumberType>& rhs) const
    {
        return {this->x * rhs.x, this->y * rhs.y};
    }

    Vector2Base<NumberType>& operator+=(const Vector2Base<NumberType>& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;

        return *this;
    }


    friend Vector2Base<NumberType> operator+(Vector2Base<NumberType> lhs, const Vector2Base<NumberType>& rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;

        return lhs;
    }

    friend Vector2Base<NumberType> operator-(Vector2Base<NumberType> lhs, const Vector2Base<NumberType>& rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;

        return lhs;
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