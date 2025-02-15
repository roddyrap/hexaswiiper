#include <stdlib.h>
#include <unistd.h>

#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <wiiuse/wiiuse.h>

#include "hexasweeper/Game.h"
#include "sprites/RectSprite.h"
#include "WiimoteCursor.h"
#include "graphics/sprites/TextSprite.h"
#include "graphics/scoped_resources.h"

#include "sprites/ImageSprite.h"

#include "Player1_png.h"
#include "WiiLogo_png.h"

#include "Roboto-Regular_ttf.h"
#include "Comfortaa-Regular_ttf.h"


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

using namespace Graphics;

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
    GRRLIB_SetBackgroundColour(200, 200, 200, 255);

    // Initialize remote pointer to the screen.
    WiimoteCursor wiimoteCursor{WPAD_CHAN_0};
    std::shared_ptr<GRRLIB_ttfFont> robotoFont = load_ttf_font(Roboto_Regular_ttf, Roboto_Regular_ttf_size);
    std::shared_ptr<GRRLIB_ttfFont> comfortaa_font = load_ttf_font(Comfortaa_Regular_ttf, Comfortaa_Regular_ttf_size);

    // ImageSprite sampleImg{Player1_png};
    Hexasweeper::Game hexasweeper_game{comfortaa_font,Vector2{256, 256}, 10, 10, 10};

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

        if (pressedButtons & WPAD_BUTTON_A)
        {
            hexasweeper_game.RevealTile(wiimoteCursor.GetPosition());
        }
        else if (pressedButtons & WPAD_BUTTON_B)
        {
            hexasweeper_game.FlagTile(wiimoteCursor.GetPosition());
        }

        Vector2Int movement{0, 0};
        if (heldButtons & WPAD_BUTTON_UP) movement.y += 1;
        if (heldButtons & WPAD_BUTTON_DOWN) movement.y -= 1;
        if (heldButtons & WPAD_BUTTON_LEFT) movement.x += 1;
        if (heldButtons & WPAD_BUTTON_RIGHT) movement.x -= 1;

        hexasweeper_game.GetTilemap().Move(Vector2{movement.x, movement.y} * 5);

        hexasweeper_game.GetTilemap().Render();

        Vector2Int coordinates = hexasweeper_game.GetTilemap().PointToCoordinates(wiimoteCursor.GetPosition());
        char *text = nullptr;
        asprintf(&text, "Current Coordinates: %d, %d", coordinates.x, coordinates.y);
        GRRLIB_PrintfTTF(0, 0, robotoFont.get(), text, 15, RGBA(255, 255, 255, 255));
        free(text);

        // WiiMote cursor should be rendered last so that it would not be covered by other objects.
        wiimoteCursor.Render();

        VIDEO_WaitVSync();
        GRRLIB_Render();
    }
}

// TODO: This project should be called 'Hexaswiiper'! it's genius!
int main(int argc, char **argv)
{
    init_wii();
    play_game();

    // Clear the memory allocated by GRRLIB
    GRRLIB_Exit(); 

    // GRRLIB docs mention using exit is preferable to return from main.
    exit(0);
}
