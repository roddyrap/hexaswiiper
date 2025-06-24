#include "HexSprite.h"

#include <cmath>

Graphics::HexSprite::HexSprite(Vector2 position, float radius, uint32_t color, bool filled) :
    RectSprite{position, HexagonSize(radius), color, filled}, m_radius{radius} {}

Graphics::HexSprite::HexSprite(Vector2 position, float radius) :
    HexSprite{position, radius, UINT32_MAX, false} {}

void Graphics::HexSprite::Render()
{
    const Vector2& center = this->GetBounds().GetCenter();
    Draw_PointyHexagon(center.x, center.y, m_radius, m_color, this->GetFill());
}

Vector2 Graphics::HexSprite::HexagonSize(float radius)
{
    // Only true for pointy hexagons.
    return {std::sqrt(3.0f) * radius, 2 * radius};
}