#include "TextSprite.h"

namespace Graphics
{
    TextSprite::TextSprite(std::shared_ptr<GRRLIB_ttfFont> font, std::string text) : TextSprite{Vector2{}, font, text, 10, UINT32_MAX}
    {}

    TextSprite::TextSprite(Vector2 position, std::shared_ptr<GRRLIB_ttfFont> font, std::string text, u32 font_size, uint32_t color) :
        RectSprite{position, Vector2{}, color, false}, m_text{text}, m_font_size{font_size}, m_font{font}
    {
        this->UpdateTextSize();
    }

    TextSprite::~TextSprite()
    {}

    void TextSprite::Render()
    {
        if (m_text.size() == 0) return;

        // Get from function to allow overloading position.
        Vector2 position = GetPosition();
        GRRLIB_PrintfTTF(static_cast<int>(position.x), static_cast<int>(position.y), m_font.get(), m_text.c_str(), m_font_size, m_color);
    }

    RectangleBounds TextSprite::GetBounds()
    {
        return RectangleBounds{this->GetPosition(), {m_size.x, m_size.y}};
    }

    void TextSprite::UpdateTextSize()
    {
        // TODO: I think the third argument is font size??
        u32 text_width = GRRLIB_WidthTTF(m_font.get(), m_text.c_str(), m_font_size);

        m_size.x = text_width;

        // TODO: This is incredibly random, I don't know how to get this.
        m_size.y = static_cast<f32>(m_font_size) * 1.2f;
    }
}