#ifndef GRAPHICS_UI_BUTTON_FACTORY_H
#define GRAPHICS_UI_BUTTON_FACTORY_H

#include "graphics/sprites/RoundedRectangleSprite.h"
#include "graphics/sprites/HexSprite.h"
#include "graphics/layouts/BoxLayout.h"
#include "graphics/ui/HoverButton.h"

namespace Graphics
{
    std::unique_ptr<HoverButton> CreateRoundedRectangleTextButton(HoverButton::callback_t callback, RectangleBounds rect_bounds, int corner_radius, std::shared_ptr<Font> font, std::string text, int font_size);

    std::unique_ptr<HoverButton> CreateHexagonTextButton(HoverButton::callback_t callback, Vector2 position, int hex_radius, std::shared_ptr<Font> font, std::string text, int font_size);
}

#endif // GRAPHICS_UI_BUTTON_FACTORY_H