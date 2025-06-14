#include "TextSprite.h"

namespace Graphics
{
    TextSprite::TextSprite(std::shared_ptr<Graphics::Font> font, const std::string& text) : TextSprite{Vector2{}, font, text, Font::DEFAULT_FONT_SIZE, UINT32_MAX}
    {}

    TextSprite::TextSprite(Vector2 position, std::shared_ptr<Graphics::Font> font, const std::string& text, u32 font_size, uint32_t color) :
        RectSprite{position, Vector2{}, color, false}, m_font{font}, m_text{text}, m_text_size{font_size}
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
        // Will only happen if text size is zero, but that's the relevant variable to check.
        if (m_cached_texture == nullptr) return;

        // Get from function to allow overloading position.
        Vector2 position = GetPosition();

#ifdef DEBUG_RENDER_TEXT_BOUNDING_BOX
        // DEBUG: Rendering text rect.
        RectSprite{position, this->GetBounds().GetSize(), RGBA(255, 0, 0, 128), true}.Render();
#endif // DEBUG_RENDER_TEXT_BOUNDING_BOX

        if (m_cached_texture != nullptr)
        {
            GRRLIB_DrawImg(position.x, position.y, m_cached_texture, 0, 1, 1, m_color);
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
        // TODO: Support multiple lines by having multiple textures (One for each line) and by
        //       rendering correctly using the measure text of each line.
        if (m_cached_texture != nullptr)
        {
            GRRLIB_FreeTexture(m_cached_texture);
        }

        if (m_text.size() == 0) return;
        m_cached_texture = m_font->Rasterize(m_text, m_text_size);
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

    void TextSprite::SetTextSize(u32 text_size)
    {
        if (m_text_size == text_size)
        {
            return;
        }

        m_text_size = text_size;
        this->RasterizeText();
    }
}