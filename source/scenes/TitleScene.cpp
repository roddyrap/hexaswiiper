#include "TitleScene.h"

#include <vector>

#include <wiiuse/wpad.h>

#include "GameScene.h"
#include "WiimoteCursor.h"
#include "graphics/sprites/ImageSprite.h"
#include "graphics/ui/ButtonFactory.h"
#include "graphics/text/Font.h"

#include "Comfortaa-Regular_ttf.h"
#include "Roboto-Regular_ttf.h"

#include "Logo1_png.h"

void TitleScene::show_title()
{
    // play_game();

    GRRLIB_SetBackgroundColour(87, 87, 87, 255);

    std::shared_ptr<FT_LibraryRec_> ft_library = Graphics::create_ft_library();
    std::shared_ptr<Graphics::Font> comfortaa_font = std::make_shared<Graphics::Font>(Comfortaa_Regular_ttf, Comfortaa_Regular_ttf_size, ft_library);
    std::shared_ptr<Graphics::Font> robot_font = std::make_shared<Graphics::Font>(Roboto_Regular_ttf, Roboto_Regular_ttf_size, ft_library);

    WiimoteCursor wiimoteCursor{WPAD_CHAN_0};

    Graphics::ImageSprite logo_sprite{Logo1_png, {0.25f, 0.25f}};
    logo_sprite.SetPosition({50, 50});

    Graphics::TextSprite logo_text{Vector2{}, comfortaa_font, "Hexaswiiper", 65, UINT32_MAX};
    Vector2 centered_position{logo_sprite.GetBounds().GetRight() + 10, logo_sprite.GetBounds().GetTop() + logo_sprite.GetBounds().GetSize().y / 2 - logo_text.GetBounds().GetSize().y / 2};
    logo_text.SetPosition(centered_position);

    Graphics::HoverButton play_button = Graphics::CreateHexagonTextButton(
        [](){ play_game(); },
        Vector2{275, 300},
        50,
        comfortaa_font,
        "Play!",
        30
    );

    std::vector<Graphics::IButton*> active_buttons{&play_button};

    while (true)
    {
        // Scan the Wiimotes (including IR).
        WPAD_ScanPads();

        uint32_t pressedButtons = WPAD_ButtonsDown(WPAD_CHAN_0);
        // uint32_t heldButtons = WPAD_ButtonsHeld(WPAD_CHAN_0);

        logo_sprite.Render();
        logo_text.Render();

        for (auto button : active_buttons)
        {
            button->Render();
            button->ReactToMouse(
                wiimoteCursor.GetPosition(),
                pressedButtons & WPAD_BUTTON_A
            );
        }

        play_button.Render();

        wiimoteCursor.Render();

        VIDEO_WaitVSync();
        GRRLIB_Render();
    }
}