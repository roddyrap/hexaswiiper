#ifndef GRAPHICS_UI_HOVER_BUTTON_H
#define GRAPHICS_UI_HOVER_BUTTON_H

#include <string>
#include <functional>

#include "graphics/sprites/RectSprite.h"
#include "graphics/sprites/TextSprite.h"
#include "graphics/sprites/RoundedRectangleSprite.h"
#include "graphics/ui/IButton.h"
#include "common/Math.h"

namespace Graphics
{
    class HoverButton : public RectSprite, public IButton
    {
    public:
        const uint64_t COLOR_LERP_TICKS = 7'000'000;
        const uint32_t HOVER_COLOR = RGBA(102, 204, 255, 255);

    public:
        HoverButton(callback_t callback, std::unique_ptr<RectSprite>&& rect_sprite);

        void Render() override;

        Vector2 GetPosition() const override;
        callback_t GetCallback() const;

        void SetPosition(Vector2 position) override;
        void SetColor(uint32_t color) override;
        void SetCurrentColor(uint32_t color);

        virtual void ReactToMouse(Vector2 mouse_position, bool is_pressed) override;

    private:
        callback_t m_callback;

        std::unique_ptr<RectSprite> m_sprite;

        uint32_t m_inactive_color;

        bool m_is_hovering{false};
        uint64_t m_hover_changed_time{};
    };
}

#endif // GRAPHICS_UI_HOVER_BUTTON_H