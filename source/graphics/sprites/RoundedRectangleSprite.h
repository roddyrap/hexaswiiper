#ifndef GRAPHICS_ROUNDED_RECTANGLE_SPRITE_H
#define GRAPHICS_ROUNDED_RECTANGLE_SPRITE_H

#include "RectSprite.h"

namespace Graphics
{
    class RoundedRectangleSprite : public RectSprite
    {
    public:
        RoundedRectangleSprite(Vector2 position, Vector2 size, uint32_t color, uint32_t border_radius, bool fill) : 
            RectSprite{position, size, color, fill}, m_border_radius{border_radius}
        {}

        virtual void Render() override;

    protected:
        uint32_t m_border_radius;
    };
}

#endif // GRAPHICS_ROUNDED_RECTANGLE_SPRITE_H