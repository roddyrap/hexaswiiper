#ifndef HEXASWEEPER_TILE_SPRITE_H
#define HEXASWEEPER_TILE_SPRITE_H

#include <memory>

#include "graphics/sprites/RectSprite.h"
#include "TileHexSprite.h"

namespace Hexasweeper::Graphics
{
    class TileSprite : public ::Graphics::Sprite
    {
    public:
        TileSprite(f32 xpos, f32 ypos, u32 radius) : TileSprite{xpos, ypos, radius, nullptr} {}
        TileSprite(f32 xpos, f32 ypos, u32 radius, std::unique_ptr<::Graphics::RectSprite>&& inner_sprite) :
            m_hexSprite{xpos, ypos, radius}, m_innerSprite{std::move(inner_sprite)}, m_xpos{xpos},
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

            if (m_innerSprite != nullptr)
            {
                m_innerSprite->SetCenter({xpos, ypos});
            }
        }

        void SetTileHexSprite(TileHexSprite&& hex_sprite)
        {
            m_hexSprite = hex_sprite;
        }

    private:
        TileHexSprite m_hexSprite;
        std::unique_ptr<::Graphics::RectSprite> m_innerSprite;

        f32 m_xpos;
        f32 m_ypos;
        u32 m_radius;
    };
}

#endif // HEXASWEEPER_TILE_SPRITE_H