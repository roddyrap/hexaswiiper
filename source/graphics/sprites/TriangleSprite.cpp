#include "TriangleSprite.h"

#include <ogc/gx.h>

#include "common/Math.h"

using namespace Graphics;

// Create equilateral triangles.
TriangleSprite::TriangleSprite(Vector2 triangle_center, int radius, uint32_t color, int rotation, bool filled) :
    RectSprite{Vector2{}, Vector2{}, color, filled},
    m_rotation{rotation},
    m_radius{radius},
    m_triangle_center{triangle_center}
{
    this->RecalculatePoints();
}

void TriangleSprite::Render()
{
    int draw_mode = this->GetFill() ? GX_TRIANGLES : GX_LINES;
    GX_Begin(draw_mode, GX_VTXFMT0, m_points.size() + !this->GetFill());
        for (const auto& point : m_points)
        {
            GX_Position3f32(point.x, point.y, 0.0f);
            GX_Color1u32(m_color);
        }

        if (!this->GetFill())
        {
            GX_Position3f32(m_points[0].x, m_points[0].y, 0.0f);
            GX_Color1u32(m_color);
        }
    GX_End();
}

bool TriangleSprite::IsPositionHovering(Vector2 position) const
{
    return this->PointInTriangle(position);
}

void TriangleSprite::SetPosition(Vector2 position)
{
    m_triangle_center += (position - m_position);
    this->RectSprite::SetPosition(position);
    this->RecalculatePoints();
}

void TriangleSprite::SetCenter(Vector2 center)
{
    m_triangle_center = center;
    this->RecalculatePoints();
}

int TriangleSprite::GetRotation() const
{
    return m_rotation;
}

void TriangleSprite::SetRotation(int rotation)
{
    m_rotation = rotation;
    this->RecalculatePoints();
}

// Thanks to: https://stackoverflow.com/a/2049593
float TriangleSprite::sign(Vector2 p1, Vector2 p2, Vector2 p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

// Thanks to: https://stackoverflow.com/a/2049593
bool TriangleSprite::PointInTriangle(Vector2 point) const
{
    float d1 = sign(point, m_points[0], m_points[1]);
    float d2 = sign(point, m_points[1], m_points[2]);
    float d3 = sign(point, m_points[2], m_points[0]);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void TriangleSprite::RecalculatePoints()
{
    m_points = {
        Vector2{m_triangle_center + PolarToCartesian(m_radius, m_rotation)},
        Vector2{m_triangle_center + PolarToCartesian(m_radius, m_rotation + 120)},
        Vector2{m_triangle_center + PolarToCartesian(m_radius, m_rotation + 240)}
    };

    RectangleBounds new_bounds{m_triangle_center, {0, 0}};
    for (const auto& point : m_points)
    {
        new_bounds.UpdateToFit(point);
    }

    m_position = new_bounds.GetTopLeft();
    m_size = new_bounds.GetSize();
}
