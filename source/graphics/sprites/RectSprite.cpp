#include "RectSprite.h"
#include <grrlib.h>

namespace Graphics
{
    void RectSprite::Render()
    {
        Vector2 position = GetPosition();
        GRRLIB_Rectangle(position.x, position.y, m_size.x, m_size.y, m_color, m_fill);
    }

    Vector2 RectSprite::GetPosition()
    {
        return m_position;
    }

    RectangleBounds RectSprite::GetBounds()
    {
        return RectangleBounds{GetPosition(), m_size};
    }
}
