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
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color, Vector2U32 size_range, Alignment x_align, Alignment y_align) :
            TextSprite{bounds.GetTopLeft(), font, text, 1, color}, m_size{bounds.GetSize()}, m_size_range{size_range}, m_x_align{x_align}, m_y_align{y_align}
        {
            this->AutofitTextSize();
        }
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color, Vector2U32 size_range) :
            AutofitTextSprite{bounds, font, text, color, size_range, Alignment::START, Alignment::START} {}
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color) :
            AutofitTextSprite{bounds, font, text, color, Vector2U32{0, UINT32_MAX}} {}

        void SetText(const std::string& text) override
        {
            this->TextSprite::SetText(text);
            this->AutofitTextSize();
        }

        void SetSize(Vector2 new_size)
        {
            m_size = new_size;
            this->AutofitTextSize();
        }

        RectangleBounds GetBounds() const override
        {
            return RectangleBounds{this->GetPosition(), m_size};
        }

        void Render() override
        {
            // Will only happen if text size is zero, but that's the relevant variable to check.
            if (m_cached_texture == nullptr) return;

            Vector2 topleft = GetPosition();
            Vector2 position{topleft};
            if (m_x_align == Alignment::START);
            else if (m_x_align == Alignment::CENTER)
            {
                position.x = topleft.x + m_size.x / 2 - m_cached_texture->w / 2;
            }
            else if (m_x_align == Alignment::END)
            {
                position.x = topleft.x + m_size.x - m_cached_texture->w;
            }

            if (m_y_align == Alignment::START);
            else if (m_y_align == Alignment::CENTER)
            {
                position.y = topleft.y + m_size.y / 2 - m_cached_texture->h / 2;
            }
            else if (m_y_align == Alignment::END)
            {
                position.y = topleft.y + m_size.y - m_cached_texture->w;
            }

            // Get from function to allow overloading position.

            GRRLIB_DrawImg(position.x, position.y, m_cached_texture, 0, 1, 1, m_color);
        }

    private:
        uint32_t GuessTextSize()
        {
            if (this->GetText().size() == 0) return m_size_range.x;

            // Find the maximum part of the range in iterations of 10.
            const uint32_t start_step_size = 10;
            uint32_t current_guess = m_size_range.x;
            Vector2Int current_measure{};
            do {
                current_guess += start_step_size;
                current_measure = this->GetFont()->MeasureText(this->GetText(), current_guess);
            } while(current_measure.x < this->m_size.x && current_measure.y < this->m_size.y && current_guess < m_size_range.y);

            uint32_t maximum = std::min(current_guess, m_size_range.y);
            uint32_t minimum = current_guess - start_step_size;

            // The loop will get stuck if maximum - minum = 0 or 1.
            while (maximum - minimum > 1)
            {
                current_guess = (maximum + minimum) / 2;
                current_measure = this->GetFont()->MeasureText(this->GetText(), current_guess);
                if (current_measure.x > this->m_size.x || current_measure.y > this->m_size.y) maximum = current_guess;
                else minimum = current_guess;
            }

            return minimum;
        }

        void AutofitTextSize()
        {
            uint32_t text_size = this->GuessTextSize();
            this->SetTextSize(text_size);
        }

    private:
        Vector2 m_size;
        Vector2U32 m_size_range{};

        Alignment m_x_align;
        Alignment m_y_align;
    };
}

#endif // GRAPHICS_SPRITES_AUTOFIT_TEXT_SPRITE_H