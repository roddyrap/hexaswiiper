#include "WiimoteCursor.h"
#include <wiiuse/wpad.h>
#include <grrlib.h>
#include "Data.h"

using namespace Graphics;

WiimoteCursor::WiimoteCursor(int wiimoteIndex) : RectSprite{Vector2{}, Vector2{32, 32}, RGBA(255, 255, 255, 255), true}, m_wiimoteIndex{wiimoteIndex}
{}

Vector2 WiimoteCursor::GetPosition()
{
    static ir_t irData;
    WPAD_IR(m_wiimoteIndex, &irData);

    return Vector2{irData.x, irData.y};
}

const uint8_t* WiimoteCursor:: GetImageByChannel(int channel)
{
    switch (channel)
    {
        case WPAD_CHAN_0:
            return Player1_png;
        default:
            return nullptr;
    }
}