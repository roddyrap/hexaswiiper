
#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H

#include <stdint.h>
#include <grrlib.h>

#include <string>
#include <memory>

#include "graphics/text/Font.h"
#include "RectSprite.h"

namespace Graphics
{
    class TextSprite : public RectSprite
    {
    public:
        TextSprite(std::shared_ptr<Graphics::Font> font, const std::string& text);
        TextSprite(Vector2 position, std::shared_ptr<Graphics::Font> font, const std::string& text, u32 font_size, u32 color);
        virtual ~TextSprite();

        virtual void Render() override;
        virtual RectangleBounds GetBounds() override;

        void SetText(const std::string& text);
        void SetTextSize(u32 text_size);

    private:
        void RasterizeText();

    private:
        std::shared_ptr<Graphics::Font> m_font;
        std::string m_text;

        GRRLIB_texImg *m_cached_texture = nullptr;

        u32 m_text_size;
    };
}

#endif // TEXT_SPRITE_H