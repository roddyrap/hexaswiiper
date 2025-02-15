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

        static constexpr u32 MIDDLE_COLOR = RGBA(80, 80, 80, 255);
        static constexpr u32 RIM_COLOR = RGBA(0, 0, 0, 255);

    public:
        TileHexSprite(f32 xpos, f32 ypos, u32 radius);
        TileHexSprite(f32 xpos, f32 ypos, u32 radius,
                      u32 rim_color, u32 middle_color, u32 inner_color);

        virtual void Render() override;

        virtual Vector2 GetPosition() override;

        void SetCenter(f32 xpos, f32 ypos);

    private:
            f32 m_xpos;
            f32 m_ypos;
            u32 m_radius;

            u32 m_rim_color;
            u32 m_middle_color;
            u32 m_inner_color;
    };
}

#endif // HEXAGON_SPRITE_H