#include "WiimoteCursor.h"
#include <wiiuse/wpad.h>
#include <grrlib.h>
#include "Data.h"

using namespace Graphics;

WiimoteCursor::WiimoteCursor(int wiimoteIndex) : ImageSprite{Vector2{}, GetImageByChannel(wiimoteIndex), RGBA(255, 255, 255, 255)}, m_wiimoteIndex{wiimoteIndex}
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

void WiimoteCursor::Render()
{
    if (this->GetTexture() == nullptr)
    {
        return;
    }

    // Get wiimote information.
    orient_t orientation{};
    WPAD_Orientation(m_wiimoteIndex, &orientation);

    // Get from function to allow overloading position.
    Vector2 position = GetPosition();
    GRRLIB_DrawImg(position.x, position.y, this->GetTexture(), orientation.roll, 1, 1, m_color);
}