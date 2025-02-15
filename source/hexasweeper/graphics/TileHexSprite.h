#ifndef HEXAGON_SPRITE_H
#define HEXAGON_SPRITE_H

#include <grrlib.h>
#include <gctypes.h>

#include "graphics/Sprite.h"
#include "graphics/Shapes.h"

namespace Hexasweeper::Graphics
{
    class TileHexSprite : public ::Graphics::Sprite
    {
    public:
        static constexpr u32 HIDDEN_INTERNAL_COLOR = RGBA(130, 130, 130, 255);
        static constexpr u32 REVEALED_INTERNAL_COLOR = RGBA(200, 200, 200, 255);

    public:
        TileHexSprite(f32 xpos, f32 ypos, u32 radius) : m_xpos{xpos}, m_ypos{ypos}, m_radius{radius}
        {

        }

        virtual void Render() override
        {
            Vector2 position = this->GetPosition();

            ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius, m_rim_color);
            ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius * 0.92, m_middle_color);
            ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius * 0.84, m_inner_color);
        }

        virtual Vector2 GetPosition() override
        {
            return Vector2{m_xpos, m_ypos};
        }

        void SetCenter(f32 xpos, f32 ypos)
        {
            m_xpos = xpos;
            m_ypos = ypos;
        }

    private:
            f32 m_xpos;
            f32 m_ypos;
            u32 m_radius;

            u32 m_rim_color{RGBA(0, 0, 0, 255)};
            u32 m_middle_color{RGBA(80, 80, 80, 255)};
            u32 m_inner_color{RGBA(130, 130, 130, 255)};
    };
}

#endif // HEXAGON_SPRITE_H