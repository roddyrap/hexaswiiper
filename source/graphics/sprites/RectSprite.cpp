#include "RectSprite.h"
#include <grrlib.h>

namespace Graphics
{
    void RectSprite::Render()
    {
        Vector2 position = GetPosition();
        GRRLIB_Rectangle(position.x, position.y, m_size.x, m_size.y, m_color, m_fill);
    }

    Vector2 RectSprite::GetPosition() const
    {
        return m_position;
    }

    Vector2 RectSprite::GetCenter() const
    {
        return this->GetBounds().GetCenter();
    }

    bool RectSprite::GetFill() const
    {
        return m_fill;
    }

    uint32_t RectSprite::GetColor() const
    {
        return m_color;
    }

    Vector2 RectSprite::GetSize() const
    {
        return m_size;
    }

    RectangleBounds RectSprite::GetBounds() const
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

    void RectSprite::SetColor(uint32_t color)
    {
        m_color = color;
    }

    void RectSprite::SetSize(Vector2 size)
    {
        m_size = size;
    }

    bool RectSprite::IsPositionHovering(Vector2 position) const
    {
        return this->GetBounds().ContainsPoint(position);
    }
}
