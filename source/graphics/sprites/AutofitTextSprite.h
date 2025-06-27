#ifndef GRAPHICS_SPRITES_AUTOFIT_TEXT_SPRITE_H
#define GRAPHICS_SPRITES_AUTOFIT_TEXT_SPRITE_H

#include "TextSprite.h"

namespace Graphics
{
    class AutofitTextSprite : public TextSprite
    {
    public:
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color, Vector2U32 size_range) :
            TextSprite{bounds.GetTopLeft(), font, text, 1, color}, m_size{bounds.GetSize()}, m_size_range{size_range}
        {
            this->AutofitTextSize();
        }
        AutofitTextSprite(RectangleBounds bounds, std::shared_ptr<Font> font, const std::string text, uint32_t color) :
            AutofitTextSprite{bounds, font, text, color, Vector2U32{0, UINT32_MAX}} {}

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

    private:
        Vector2 m_size;
        Vector2U32 m_size_range{};
    };
}

#endif // GRAPHICS_SPRITES_AUTOFIT_TEXT_SPRITE_H