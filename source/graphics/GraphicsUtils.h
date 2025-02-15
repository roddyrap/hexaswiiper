#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include "common/Vector2.h"

namespace Graphics
{
    class RectangleBounds
    {
    public:
        RectangleBounds(Vector2 topLeft, Vector2 size) : m_topLeft{topLeft}, m_size{size} {}
        float GetRight();
        float GetLeft();
        float GetTop();
        float GetBottom();

        Vector2 GetTopLeft();
        Vector2 GetTopRight();
        Vector2 GetBottomLeft();
        Vector2 GetBottomRight();

        Vector2 GetSize();

    private:
        Vector2 m_topLeft;
        Vector2 m_size;
    };
}

#endif // GRAPHICS_UTILS_H