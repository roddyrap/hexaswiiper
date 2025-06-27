
#ifndef IMAGE_SPRITE_H
#define IMAGE_SPRITE_H

#include <stdint.h>
#include <grrlib.h>

#include "RectSprite.h"

namespace Graphics
{
    class ImageSprite : public RectSprite
    {
    public:
        ImageSprite(const uint8_t* imageData);
        ImageSprite(const uint8_t* imageData, Vector2 scale);
        ImageSprite(Vector2 position, const uint8_t* imageData, Vector2 scale, uint32_t color);
        ImageSprite(Vector2 position, const uint8_t* imageData, Vector2 scale, uint32_t color, uint32_t rotation);

        ~ImageSprite();

        virtual void Render() override;
        virtual RectangleBounds GetBounds() const override;

        Vector2 GetScale();
    protected:
        virtual GRRLIB_texImg* GetTexture();

    private:
        GRRLIB_texImg* m_texture{nullptr};
        Vector2 m_scale;

        uint32_t m_rotation;
    };
}

#endif // IMAGE_SPRITE_H