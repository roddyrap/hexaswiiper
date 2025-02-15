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
        TileHexSprite(f32 xpos, f32 ypos, u32 radius) : m_xpos{xpos}, m_ypos{ypos}, m_radius{radius}
        {

        }

        virtual void Render() override
        {
            Vector2 position = this->GetPosition();

            ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius, RGBA(0, 0, 0, 255));
            ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius * 0.92, RGBA(80, 80, 80, 255));
            ::Graphics::Draw_PointyHexagon(position.x, position.y, m_radius * 0.84, RGBA(130, 130, 130, 255));
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
    };
}

#endif // HEXAGON_SPRITE_H