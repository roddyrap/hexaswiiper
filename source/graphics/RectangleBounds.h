#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include "common/Vector2.h"

namespace Graphics
{
    class RectangleBounds
    {
    public:
        RectangleBounds() : m_topLeft{}, m_size{} {}
        RectangleBounds(Vector2 topLeft, Vector2 size) : m_topLeft{topLeft}, m_size{size} {}
        float GetRight() const;
        float GetLeft() const;
        float GetTop() const;
        float GetBottom() const;

        Vector2 GetTopLeft() const;
        Vector2 GetTopRight() const;
        Vector2 GetBottomLeft() const;
        Vector2 GetBottomRight() const;

        Vector2 GetSize() const;

        bool ContainsPoint(Vector2 point) const;

        void UpdateToFit(Vector2 point);
    private:
        Vector2 m_topLeft;
        Vector2 m_size;
    };
}

#endif // GRAPHICS_UTILS_H