#include "TextSprite.h"

namespace Graphics
{
    TextSprite::TextSprite(std::shared_ptr<Graphics::Font> font, const std::string& text) : TextSprite{Vector2{}, font, text, 10, UINT32_MAX}
    {}

    TextSprite::TextSprite(Vector2 position, std::shared_ptr<Graphics::Font> font, const std::string& text, u32 font_size, uint32_t color) :
        RectSprite{position, Vector2{}, color, false}, m_font{font}, m_text{text}, m_font_size{font_size}
    {
        this->RasterizeText();
    }

    TextSprite::~TextSprite()
    {
        if (m_cached_texture != nullptr)
        {
            GRRLIB_FreeTexture(m_cached_texture);
        }
    }

    void TextSprite::Render()
    {
        if (m_text.size() == 0) return;

        // Get from function to allow overloading position.
        Vector2 position = GetPosition();
        if (m_cached_texture != nullptr)
        {
            GRRLIB_DrawImg(static_cast<int>(position.x), static_cast<int>(position.y), m_cached_texture, 0, 1, 1, m_color);
        }
    }

    RectangleBounds TextSprite::GetBounds()
    {
        Vector2 size{0, 0};
        if (m_cached_texture != nullptr)
        {
            size = Vector2{static_cast<float>(m_cached_texture->w), static_cast<float>(m_cached_texture->h)};
        }

        return RectangleBounds{this->GetPosition(), size};
    }

    void TextSprite::RasterizeText()
    {
        if (m_cached_texture != nullptr)
        {
            GRRLIB_FreeTexture(m_cached_texture);
        }

        m_cached_texture = m_font->Rasterize(m_text);
    }

    void TextSprite::SetText(const std::string& text)
    {
        // Don't rasterize if the text is the same.
        if (m_text == text) 
        {
            return;
        }

        m_text = text;
        this->RasterizeText();
    }
}