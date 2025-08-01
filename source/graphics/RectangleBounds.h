#ifndef GRAPHICS_RECTANGLE_BOUNDS_H
#define GRAPHICS_RECTANGLE_BOUNDS_H

#include "common/Vector2.h"

namespace Graphics
{
    class RectangleBounds
    {
    public:
        RectangleBounds() : m_topLeft{}, m_size{} {}
        RectangleBounds(Vector2 topLeft, Vector2 size) : m_topLeft{topLeft}, m_size{size} {}
        RectangleBounds(float topX, float topY, float sizeX, float sizeY) : m_topLeft{topX, topY}, m_size{sizeX, sizeY} {}

        float GetRight() const;
        float GetLeft() const;
        float GetTop() const;
        float GetBottom() const;

        Vector2 GetTopLeft() const;
        Vector2 GetTopRight() const;
        Vector2 GetBottomLeft() const;
        Vector2 GetBottomRight() const;

        Vector2 GetCenter() const;

        Vector2 GetSize() const;
        float GetArea() const;

        bool ContainsPoint(Vector2 point) const;

        void UpdateToFit(Vector2 point);
        void UpdateToFit(RectangleBounds bounds);
        RectangleBounds Intersection(const RectangleBounds& other) const;

        private:
        Vector2 m_topLeft;
        Vector2 m_size;
    };
}

#endif // GRAPHICS_RECTANGLE_BOUNDS_H
