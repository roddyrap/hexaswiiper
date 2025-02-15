
#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H

#include <stdint.h>
#include <grrlib.h>

#include <string>
#include <memory>

#include "RectSprite.h"
#include "graphics/TTFFont.h"

namespace Graphics
{
    class TextSprite : public RectSprite
    {
    public:
        TextSprite(std::shared_ptr<TTFFont> font, std::string text);
        TextSprite(Vector2 position, std::shared_ptr<TTFFont> font, std::string text, u32 font_size, u32 color);
        ~TextSprite();

        virtual void Render() override;
        virtual RectangleBounds GetBounds() override;

    private:
        void UpdateTextSize();

    private:
        std::shared_ptr<TTFFont> m_font;
        std::string m_text{};

        u32 m_font_size{10};
    };
}

#endif // TEXT_SPRITE_H