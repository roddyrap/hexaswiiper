#ifndef GRAPHICS_SPRITES_HEX_SPRITE_H
#define GRAPHICS_SPRITES_HEX_SPRITE_H

#include <grrlib.h>

#include "graphics/sprites/RectSprite.h"
#include "graphics/Shapes.h"

namespace Graphics
{
    class HexSprite : public RectSprite
    {
    public:
        HexSprite(Vector2 position, float radius, uint32_t color, bool filled);
        HexSprite(Vector2 position, float radius);

        virtual void Render() override;

        static Vector2 HexagonSize(float radius);

    private:
            float m_radius;
    };
}

#endif // GRAPHICS_SPRITES_HEX_SPRITE_H