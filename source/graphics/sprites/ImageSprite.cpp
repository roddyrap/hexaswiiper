#include "ImageSprite.h"

namespace Graphics
{
    ImageSprite::ImageSprite(const uint8_t* imageData) : ImageSprite{imageData, Vector2{1, 1}}
    {}

    ImageSprite::ImageSprite(const uint8_t* imageData, Vector2 scale) : ImageSprite{Vector2{}, imageData, scale, 0xFFFFFFFF}
    {}

    ImageSprite::ImageSprite(Vector2 position, const uint8_t* imageData, Vector2 scale, uint32_t color) :
        RectSprite{position, Vector2{}, color, false}, m_scale{scale}
    {
        m_texture = GRRLIB_LoadTexture(imageData);
        if (m_texture == nullptr)
        {
            return;
        }

        m_size.x = m_texture->w;
        m_size.y = m_texture->h;
    }

    ImageSprite::~ImageSprite()
    {
        if (m_texture != nullptr)
        {
            GRRLIB_FreeTexture(m_texture);
        }
    }

    void ImageSprite::Render()
    {
        if (m_texture == nullptr)
        {
            return;
        }

        // Get from function to allow overloading position.
        Vector2 position = GetPosition();
        GRRLIB_DrawImg(position.x, position.y, m_texture, 0, m_scale.x, m_scale.y, m_color);
    }

    RectangleBounds ImageSprite::GetBounds()
    {
        return RectangleBounds{GetPosition(), Vector2{m_texture->w, m_texture->h} * m_scale};
    }

    GRRLIB_texImg* ImageSprite::GetTexture()
    {
        return m_texture;
    }
}