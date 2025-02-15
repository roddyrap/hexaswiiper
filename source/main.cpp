#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <wiiuse/wiiuse.h>

#include "sprites/RectSprite.h"
#include "WiimoteCursor.h"
#include "TTFont.h"

#include "sprites/ImageSprite.h"

#include "Player1_png.h"
#include "WiiLogo_png.h"

#include "Roboto-Regular_ttf.h"

#include <unistd.h>

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
    // ImageSprite cursorImage{Vector2{}, Player1_png, ACTUAL_WHITE};
    TTFont robotoFont{Roboto_Regular_ttf, Roboto_Regular_ttf_size};

    // ImageSprite sampleImg{Player1_png};

    GRRLIB_texImg* newTexture = GRRLIB_LoadTexturePNG(WiiLogo_png);

    // Loop forever (gameloop).
    while(true)
    {
        // Scan the Wiimotes (including IR).
        WPAD_ScanPads();

        u32 pressedButtons = WPAD_ButtonsDown(WPAD_CHAN_0);

        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (pressedButtons & WPAD_BUTTON_HOME)
        {
            break;
        }

        // The Sprite class keeps track of all active sprites, so it isn't needed to be done manually.
        Sprite::RenderActive();

        robotoFont.Printf(Vector2Int{0, 10}, "Image size: %d, %d", newTexture->w, newTexture->h);
        GRRLIB_DrawImg(10, 50, newTexture, 0, 1, 1, ACTUAL_WHITE);

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
