
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
        ImageSprite(Vector2 position, const uint8_t* imageData, uint32_t color);
        ~ImageSprite();

        virtual void Render() override;
        virtual Vector2 GetPosition() override;

    protected:
        virtual GRRLIB_texImg* GetTexture();

    private:
        GRRLIB_texImg* m_texture{nullptr};
    };
}

#endif // IMAGE_SPRITE_H