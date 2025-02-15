#ifndef HEXASWEEPER_TILE_SPRITE_H
#define HEXASWEEPER_TILE_SPRITE_H

#include <memory>

#include "TileHexSprite.h"

namespace Hexasweeper::Graphics
{
    class TileSprite : public ::Graphics::Sprite
    {
    public:
        TileSprite(f32 xpos, f32 ypos, u32 radius) :
            m_hexSprite{xpos, ypos, radius}, m_innerSprite{nullptr}, m_xpos{xpos},
            m_ypos{ypos}, m_radius{radius} {}

        virtual void Render() override
        {
            m_hexSprite.Render();

            if (m_innerSprite != nullptr)
            {
                m_innerSprite->Render();
            }
        }

        virtual Vector2 GetPosition() override
        {
            return Vector2{m_xpos, m_ypos};
        }

        void SetCenter(Vector2 center)
        {
            this->SetCenter(center.x, center.y);
        }

        void SetCenter(f32 xpos, f32 ypos)
        {
            m_xpos = xpos;
            m_ypos = ypos;

            m_hexSprite.SetCenter(xpos, ypos);
            // TODO: Set inner sprite's center (probably need centerable concept). 
        }

    private:
        TileHexSprite m_hexSprite;
        std::unique_ptr<::Graphics::Sprite> m_innerSprite;

        f32 m_xpos;
        f32 m_ypos;
        u32 m_radius;
    };
}

#endif // HEXASWEEPER_TILE_SPRITE_H