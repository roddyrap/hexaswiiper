#ifndef COMMON_GRAPHICS_UI_TEXT_BUTTON_H

#include <string>
#include <functional>

#include "graphics/sprites/RectSprite.h"
#include "graphics/sprites/TextSprite.h"
#include "graphics/sprites/RoundedRectangleSprite.h"

namespace Graphics
{
    class TextButton : public RoundedRectangleSprite
    {
    public:
        using callback_t = std::function<void(void)>;

    public:
        TextButton(callback_t callback, RectangleBounds rectangle, std::shared_ptr<Font> font, std::string text, unsigned int font_size) :
            RoundedRectangleSprite{rectangle.GetTopLeft(), rectangle.GetSize(), UINT32_MAX, 5, false},
            m_callback{callback},
            m_text_sprite{rectangle.GetTopLeft(), font, text, font_size, UINT32_MAX}
        {
            this->PositionText();
        }

        void Render() override
        {
            m_text_sprite.Render();
            this->RoundedRectangleSprite::Render();
        }

        void SetPosition(Vector2 position) override
        {
            this->RoundedRectangleSprite::SetPosition(position);
            this->PositionText();
        }

        void ReactToMouse(Vector2 mouse_position, bool is_pressed)
        {
            if (is_pressed && this->GetBounds().ContainsPoint(mouse_position))
            {
                this->Call();
            }
        }

        void Call()
        {
            m_callback();
        }

    private:
        void PositionText()
        {
            // Center text to button (Does not clip in case of overflow).
            Vector2 text_size = m_text_sprite.GetBounds().GetSize();
            Vector2 centered_text_position = this->GetBounds().GetCenter() - Vector2{text_size.x / 2.0f, text_size.y / 2.0f};

            m_text_sprite.SetPosition(centered_text_position);
        }

    private:
        callback_t m_callback;
        TextSprite m_text_sprite;
    };
}

#endif // COMMON_GRAPHICS_UI_TEXT_BUTTON_H