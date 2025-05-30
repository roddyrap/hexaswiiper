#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <wiiuse/wiiuse.h>

#include "hexasweeper/Game.h"
#include "sprites/RectSprite.h"
#include "WiimoteCursor.h"
#include "graphics/sprites/TextSprite.h"
#include "graphics/text/Font.h"

#include "sprites/ImageSprite.h"

#include "Player1_png.h"
#include "WiiLogo_png.h"
#include "Logo1_png.h"

#include "Roboto-Regular_ttf.h"
#include "Comfortaa-Regular_ttf.h"

#include <format>


#define ASSERT(expression)                   \
        do                                   \
        {                                    \
            if (!(expression))               \
            {                                \
                GRRLIB_Exit();               \
                exit(1);                     \
            }                                \
        } while (false);

constexpr uint32_t ACTUAL_WHITE = RGBA(255, 255, 255, 255);
constexpr uint32_t ACTUAL_BLACK = RGBA(0, 0, 0, 255);

using namespace Graphics;

std::string FormatDuration(uint64_t duration_seconds)
{
    return std::format(
        "{:02}:{:02}:{:02}",
        duration_seconds / 3600,
        (duration_seconds % 3600) / 60,
        duration_seconds % 60
    );
}

void init_wii()
{
    // Initialise the Graphics & Video subsystem
    ASSERT(GRRLIB_Init() == 0) ;

    // Initialise the Wiimotes with IR.
    ASSERT(WPAD_Init() == 0);
    ASSERT(WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR) == 0);

    // Rmode is defined, somewhere....
    rmode = VIDEO_GetPreferredMode(nullptr);
    ASSERT(WPAD_SetVRes(WPAD_CHAN_0, rmode->fbWidth, rmode->xfbHeight) == 0);
}

// A separate scope that closes before GRRLIB_Exit in order to ensure clean destructors.
void play_game()
{
    GRRLIB_SetBackgroundColour(87, 87, 87, 255);

    // Initialize remote pointer to the screen.
    WiimoteCursor wiimoteCursor{WPAD_CHAN_0};

    std::shared_ptr<FT_LibraryRec_> ft_library = create_ft_library();
    std::shared_ptr<Graphics::Font> roboto_font = std::make_shared<Graphics::Font>(Roboto_Regular_ttf, Roboto_Regular_ttf_size, ft_library);
    std::shared_ptr<Graphics::Font> comfortaa_font = std::make_shared<Graphics::Font>(Comfortaa_Regular_ttf, Comfortaa_Regular_ttf_size, ft_library);

    // Initialize screen regions.
    RectangleBounds game_region = RectangleBounds{{5, 60}, {500, 415}};
    RectangleBounds settings_region = RectangleBounds{{510, 60}, {125, 80}};
    RectangleBounds info_region = RectangleBounds{{510, 145}, {125, 330}};

    // Initialize UI.
    ImageSprite logo_sprite{Logo1_png, {0.1f, 0.1f}};
    TextSprite logo_text{comfortaa_font, "Hexaswiiper"};
    logo_sprite.SetPosition({5, 2});
    logo_text.SetPosition({logo_sprite.GetBounds().GetRight() + 8, 13});

    // Initialize tilemap & game.
    Hexasweeper::Game hexasweeper_game{comfortaa_font, Vector2{}, 10, 10, 10};
    Hexasweeper::Graphics::Tilemap& tilemap = hexasweeper_game.GetTilemap();
    tilemap.SetTopLeft(game_region.GetTopLeft());

    // TODO: The clipping isn't perfect, the region border is a rounded rectangle which means that
    //       the corners are incorrect (Not clipped). This is known. My idea for solving it is by
    //       rendering the inverse of the rounded rectangle after the tilemap, which would cover
    //       the edges. Will also need to treat remote presses on the edges.
    tilemap.SetClipRect(game_region);

    // Initialize info sprites.
    TextSprite settings_text{roboto_font, "Difficulty: Whatever"};
    settings_text.SetPosition(settings_region.GetTopLeft() + Vector2{2, 10});
    settings_text.SetTextSize(14);

    TextSprite flags_left_text{roboto_font, ""};
    flags_left_text.SetPosition(info_region.GetTopLeft() + Vector2{2, 10});
    flags_left_text.SetTextSize(15);

    TextSprite time_text{roboto_font, ""};
    time_text.SetPosition(info_region.GetTopLeft() + Vector2{2, 30});
    time_text.SetTextSize(15);

    // Loop forever (gameloop).
    while(true)
    {
        // Scan the Wiimotes (including IR).
        WPAD_ScanPads();

        u32 pressedButtons = WPAD_ButtonsDown(WPAD_CHAN_0);
        u32 heldButtons = WPAD_ButtonsHeld(WPAD_CHAN_0);

        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (pressedButtons & WPAD_BUTTON_HOME)
        {
            break;
        }

        if (tilemap.GetClipRect().has_value() && tilemap.GetClipRect()->ContainsPoint(wiimoteCursor.GetPosition()))
        {
            if (pressedButtons & WPAD_BUTTON_A)
            {
                hexasweeper_game.RevealTile(wiimoteCursor.GetPosition());
            }
            else if (pressedButtons & WPAD_BUTTON_B)
            {
                hexasweeper_game.FlagTile(wiimoteCursor.GetPosition());
            }
        }

        Vector2 movement{0, 0};
        if (heldButtons & WPAD_BUTTON_UP) movement.y += 1.0;
        if (heldButtons & WPAD_BUTTON_DOWN) movement.y -= 1.0;
        if (heldButtons & WPAD_BUTTON_LEFT) movement.x += 1.0;
        if (heldButtons & WPAD_BUTTON_RIGHT) movement.x -= 1.0;

        hexasweeper_game.GetTilemap().Move(movement * 5);
        
        // Draw game.
        hexasweeper_game.GetTilemap().Render();

        // Draw UI
        logo_sprite.Render();
        logo_text.Render();

        // Draw information. (Part of UI)
        settings_text.Render();

        Hexasweeper::Logic::Board& board = hexasweeper_game.GetBoard();
        std::string flags_left_string{};
        flags_left_string += std::format("Flags Left: {}/{}", board.GetFlagsLeft(), board.GetNumBombs());
        flags_left_text.SetText(flags_left_string);
        flags_left_text.Render();

        std::string time_passed_string{};
        if (hexasweeper_game.GetStartTime() == 0)
        {
            time_passed_string += std::string{"Not started yet"};
        }
        else
        {
            time_passed_string += std::string{"Time: "} + FormatDuration(time(nullptr) - hexasweeper_game.GetStartTime());
        }
        time_text.SetText(time_passed_string);
        time_text.Render();

        // Draw UI regions.
        Draw_RoundedRectangle(game_region, 5, ACTUAL_BLACK, false);
        Draw_RoundedRectangle(settings_region, 5, ACTUAL_BLACK, false);
        Draw_RoundedRectangle(info_region, 5, ACTUAL_BLACK, false);

        // WiiMote cursor should be rendered last so that it would not be covered by other objects.
        wiimoteCursor.Render();


        VIDEO_WaitVSync();
        GRRLIB_Render();
    }
}

int main(int argc, char **argv)
{
    init_wii();
    play_game();

    // Clear the memory allocated by GRRLIB
    GRRLIB_Exit(); 

    // GRRLIB docs mention using exit is preferable to return from main.
    exit(0);
}
