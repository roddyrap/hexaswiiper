#include "ButtonFactory.h"

namespace Graphics
{
    std::unique_ptr<HoverButton> CreateRoundedRectangleTextButton(HoverButton::callback_t callback, RectangleBounds rect_bounds, int corner_radius, std::shared_ptr<Font> font, std::string text, int font_size)
    {
        std::unique_ptr<RoundedRectangleSprite> rect_sprite = std::make_unique<RoundedRectangleSprite>(rect_bounds.GetTopLeft(), rect_bounds.GetSize(), UINT32_MAX, corner_radius, false);
        std::unique_ptr<TextSprite> text_sprite = std::make_unique<TextSprite>(rect_bounds.GetTopLeft(), font, text, font_size, UINT32_MAX);

        std::unique_ptr<BoxLayout> box_layout = std::make_unique<BoxLayout>(rect_bounds, true);
        box_layout->AddSprite(std::move(rect_sprite));
        box_layout->AddSprite(std::move(text_sprite));

        return std::make_unique<HoverButton>(callback, std::move(box_layout));
    }

    std::unique_ptr<HoverButton> CreateHexagonTextButton(HoverButton::callback_t callback, Vector2 position, int hex_radius, std::shared_ptr<Font> font, std::string text, int font_size)
    {
        std::unique_ptr<HexSprite> hex_sprite = std::make_unique<HexSprite>(position, hex_radius, UINT32_MAX, false);
        std::unique_ptr<TextSprite> text_sprite = std::make_unique<TextSprite>(Vector2{}, font, text, font_size, UINT32_MAX);

        std::unique_ptr<BoxLayout> box_layout = std::make_unique<BoxLayout>(hex_sprite->GetBounds(), true);
        box_layout->AddSprite(std::move(hex_sprite));
        box_layout->AddSprite(std::move(text_sprite));

        return std::make_unique<HoverButton>(callback, std::move(box_layout));
    }
}
