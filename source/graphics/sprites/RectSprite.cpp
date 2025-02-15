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

    void RectSprite::SetPosition(Vector2 position)
    {
        m_position = position;
    }

    void RectSprite::SetCenter(Vector2 position)
    {
        Vector2 size = this->GetBounds().GetSize();
        this->SetPosition(Vector2{position.x - size.x / 2, position.y - size.y / 2});
    }
}
