#ifndef GRAPHICS_SPRITES_AUTOFIT_TEXT_SPRITE_H
#define GRAPHICS_SPRITES_AUTOFIT_TEXT_SPRITE_H

#include "TextSprite.h"

namespace Graphics
{
    enum class Alignment
    {
        START,
        CENTER,
        END
    };

    class AutofitTextSprite : public TextSprite
    {
    public:
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color, Vector2U32 size_range, Alignment x_align, Alignment y_align);
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color, Vector2U32 size_range);
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color);

        void SetText(const std::string& text) override;
        void SetSize(Vector2 new_size);

        RectangleBounds GetBounds() const override;

        void Render() override;

    private:
        uint32_t GuessTextSize();
        void AutofitTextSize();

    private:
        Vector2 m_size;
        Vector2U32 m_size_range{};

        Alignment m_x_align;
        Alignment m_y_align;
    };
}

#endif // GRAPHICS_SPRITES_AUTOFIT_TEXT_SPRITE_H