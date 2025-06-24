#include "RectangleBounds.h"

namespace Graphics
{
    float RectangleBounds::GetRight() const
    {
        return m_topLeft.x + m_size.x;
    }

    float RectangleBounds::GetLeft() const
    {
        return m_topLeft.x;
    }

    float RectangleBounds::GetTop() const
    {
        return m_topLeft.y;
    }

    float RectangleBounds::GetBottom() const
    {
        return m_topLeft.y + m_size.y;
    }


    Vector2 RectangleBounds::GetTopLeft() const
    {
        return m_topLeft;
    }

    Vector2 RectangleBounds::GetTopRight() const
    {
        return Vector2{m_topLeft.x + m_size.x, m_topLeft.y};
    }

    Vector2 RectangleBounds::GetBottomLeft() const
    {
        return Vector2{m_topLeft.x, m_topLeft.y + m_size.y};
    }

    Vector2 RectangleBounds::GetBottomRight() const
    {
        return Vector2{m_topLeft.x + m_size.x, m_topLeft.y + m_size.y};
    }

    Vector2 RectangleBounds::GetCenter() const
    {
        return Vector2{m_topLeft.x + m_size.x / 2.0f, m_topLeft.y + m_size.y / 2.0f};
    }

    Vector2 RectangleBounds::GetSize() const
    {
        return m_size;
    }

    float RectangleBounds::GetArea() const
    {
        return m_size.x * m_size.y;
    }

    bool RectangleBounds::ContainsPoint(Vector2 point) const
    {
        return point.x >= GetLeft() && point.x <= GetRight() && point.y >= GetTop() && point.y <= GetBottom();
    }

    void RectangleBounds::UpdateToFit(Vector2 point)
    {
        if (this->ContainsPoint(point)) return;

        if (point.x < GetLeft())
        {
            float right = GetRight();
            m_topLeft.x = point.x;
            m_size.x = right - m_topLeft.x;
        }
        else if (point.x > GetRight())
        {
            m_size.x = point.x - m_topLeft.x;
        }

        if (point.y < GetTop())
        {
            float bottom = GetBottom();
            m_topLeft.y = point.y;
            m_size.y = bottom - m_topLeft.y;
        }
        else if (point.y > GetBottom())
        {
            m_size.y = point.y - m_topLeft.y;
        }
    }

    void RectangleBounds::UpdateToFit(RectangleBounds bounds)
    {
        this->UpdateToFit(bounds.GetTopLeft());
        this->UpdateToFit(bounds.GetTopRight());
        this->UpdateToFit(bounds.GetBottomLeft());
        this->UpdateToFit(bounds.GetBottomRight());
    }
}
