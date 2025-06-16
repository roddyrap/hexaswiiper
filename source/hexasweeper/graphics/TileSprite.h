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
        TileSprite(f32 xpos, f32 ypos, u32 radius);
        TileSprite(f32 xpos, f32 ypos, u32 radius, std::unique_ptr<::Graphics::RectSprite>&& inner_sprite);

        virtual void Render() override;

        virtual Vector2 GetPosition() const override;

        void SetCenter(Vector2 center);

        void SetCenter(f32 xpos, f32 ypos);

        void SetTileHexSprite(TileHexSprite&& hex_sprite);

    private:
        TileHexSprite m_hexSprite;
        std::unique_ptr<::Graphics::RectSprite> m_innerSprite;

        f32 m_xpos;
        f32 m_ypos;
        u32 m_radius;
    };
}

#endif // HEXASWEEPER_TILE_SPRITE_H