
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

        // Disallow copies because of the raw pointer that is handled by this class.
        TextSprite(TextSprite& other) = delete;

        virtual void Render() override;
        virtual RectangleBounds GetBounds() const override;
        virtual std::shared_ptr<Font> GetFont() const;
        virtual const std::string& GetText() const;

        virtual void SetText(const std::string& text);
        virtual void SetTextSize(u32 text_size);

    private:
        void RasterizeText();

    protected:
        GRRLIB_texImg *m_cached_texture = nullptr;

    private:
        std::shared_ptr<Graphics::Font> m_font;
        std::string m_text;

        u32 m_text_size;
    };
}

#endif // TEXT_SPRITE_H