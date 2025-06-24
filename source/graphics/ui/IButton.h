#ifndef GRAPHICS_UI_BASE_BUTTON_H
#define GRAPHICS_UI_BASE_BUTTON_H

#include <string>
#include <functional>

#include "common/Vector2.h"

#include <grrlib.h>

namespace Graphics
{
    class IButton : public virtual Sprite
    {
    public:
        using callback_t = std::function<void(void)>;

    public:
        virtual ~IButton() = default;

        virtual void ReactToMouse(Vector2 mouse_position, bool is_pressed) = 0;

        virtual void Call()
        {
            this->GetCallback()();
        }

        virtual callback_t GetCallback() const = 0;
    };
}

#endif // GRAPHICS_UI_BASE_BUTTON_H