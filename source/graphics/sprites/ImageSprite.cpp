#include "ImageSprite.h"

namespace Graphics
{
    ImageSprite::ImageSprite(const uint8_t* imageData) : ImageSprite{Vector2{}, imageData, 0xFFFFFFFF}
    {}

    ImageSprite::ImageSprite(Vector2 position, const uint8_t* imageData, uint32_t color) :
        RectSprite{position, Vector2{}, color, false}
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
        GRRLIB_DrawImg(position.x, position.y, m_texture, 0, 1, 1, m_color);
    }

    Vector2 ImageSprite::GetPosition()
    {
        return m_position;
    }

    GRRLIB_texImg* ImageSprite::GetTexture()
    {
        return m_texture;
    }
}