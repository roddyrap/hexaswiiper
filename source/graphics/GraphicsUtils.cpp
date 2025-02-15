#include "GraphicsUtils.h"

namespace Graphics
{
    float RectangleBounds::GetRight()
    {
        return m_topLeft.x + m_size.x;
    }

    float RectangleBounds::GetLeft()
    {
        return m_topLeft.x;
    }

    float RectangleBounds::GetTop()
    {
        return m_topLeft.y;
    }

    float RectangleBounds::GetBottom()
    {
        return m_topLeft.y + m_size.y;
    }


    Vector2 RectangleBounds::GetTopLeft()
    {
        return m_topLeft;
    }

    Vector2 RectangleBounds::GetTopRight()
    {
        return Vector2{m_topLeft.x + m_size.x, m_topLeft.y};
    }

    Vector2 RectangleBounds::GetBottomLeft()
    {
        return Vector2{m_topLeft.x, m_topLeft.y + m_size.y};
    }

    Vector2 RectangleBounds::GetBottomRight()
    {
        return Vector2{m_topLeft.x + m_size.x, m_topLeft.y + m_size.y};
    }

    Vector2 RectangleBounds::GetSize()
    {
        return m_size;
    }
}
