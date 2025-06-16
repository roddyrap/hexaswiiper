#include "WiimoteCursor.h"
#include <wiiuse/wpad.h>
#include <grrlib.h>
#include "cursor1_png.h"
#include "cursor2_png.h"
#include "cursor3_png.h"
#include "cursor4_png.h"

WiimoteCursor::WiimoteCursor(int wiimoteIndex) :
    ImageSprite{Vector2{}, GetImageByChannel(wiimoteIndex), Vector2{0.05f, 0.05f}, UINT32_MAX}, m_wiimoteIndex{wiimoteIndex}
{}

Vector2 WiimoteCursor::GetPosition() const
{
    static ir_t irData;
    WPAD_IR(m_wiimoteIndex, &irData);

    return Vector2{irData.x, irData.y};
}

const uint8_t* WiimoteCursor::GetImageByChannel(int channel)
{
    switch (channel)
    {
        case WPAD_CHAN_0:
            return cursor1_png;
        case WPAD_CHAN_1:
            return cursor2_png;
        case WPAD_CHAN_2:
            return cursor3_png;
        case WPAD_CHAN_3:
            return cursor4_png;
        default:
            return cursor1_png;
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
    Vector2 scale = GetScale();
    GRRLIB_DrawImg(position.x, position.y, this->GetTexture(), orientation.roll, scale.x, scale.y, m_color);
}