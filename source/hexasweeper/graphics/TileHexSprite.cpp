#include "TileHexSprite.h"

Hexasweeper::Graphics::TileHexSprite::TileHexSprite(f32 xpos, f32 ypos, u32 radius) :
    TileHexSprite{xpos, ypos, radius, RIM_COLOR, MIDDLE_COLOR, HIDDEN_INTERNAL_COLOR}
{}

Hexasweeper::Graphics::TileHexSprite::TileHexSprite(f32 xpos, f32 ypos, u32 radius, u32 rim_color, u32 middle_color, u32 inner_color) :
    m_xpos{xpos}, m_ypos{ypos}, m_radius{radius}, m_rim_color{rim_color}, m_middle_color{middle_color}, m_inner_color{inner_color} {}


void Hexasweeper::Graphics::TileHexSprite::Render()
{
    Vector2 position = this->GetPosition();

    ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius, m_rim_color);
    ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius * 0.92, m_middle_color);
    ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius * 0.84, m_inner_color);
}

Vector2 Hexasweeper::Graphics::TileHexSprite::GetPosition()
{
    return Vector2{m_xpos, m_ypos};
}

void Hexasweeper::Graphics::TileHexSprite::SetCenter(f32 xpos, f32 ypos)
{
    m_xpos = xpos;
    m_ypos = ypos;
}