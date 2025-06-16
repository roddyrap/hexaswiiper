#include "TileSprite.h"

#include <gctypes.h>

using namespace Hexasweeper::Graphics;

Hexasweeper::Graphics::TileSprite::TileSprite(f32 xpos, f32 ypos, u32 radius) : TileSprite{xpos, ypos, radius, nullptr} {}
Hexasweeper::Graphics::TileSprite::TileSprite(f32 xpos, f32 ypos, u32 radius, std::unique_ptr<::Graphics::RectSprite>&& inner_sprite) :
    m_hexSprite{xpos, ypos, radius}, m_innerSprite{std::move(inner_sprite)}, m_xpos{xpos},
    m_ypos{ypos}, m_radius{radius} {}

void Hexasweeper::Graphics::TileSprite::Render()
{
    m_hexSprite.Render();

    if (m_innerSprite != nullptr)
    {
        m_innerSprite->Render();
    }
}

Vector2 Hexasweeper::Graphics::TileSprite::GetPosition() const
{
    return Vector2{m_xpos, m_ypos};
}

void Hexasweeper::Graphics::TileSprite::SetCenter(Vector2 center)
{
    this->SetCenter(center.x, center.y);
}

void Hexasweeper::Graphics::TileSprite::SetCenter(f32 xpos, f32 ypos)
{
    m_xpos = xpos;
    m_ypos = ypos;

    m_hexSprite.SetCenter(xpos, ypos);

    if (m_innerSprite != nullptr)
    {
        m_innerSprite->SetCenter({xpos, ypos});
    }
}

void Hexasweeper::Graphics::TileSprite::SetTileHexSprite(TileHexSprite&& hex_sprite)
{
    m_hexSprite = hex_sprite;
}