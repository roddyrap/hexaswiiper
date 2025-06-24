#ifndef WIIMOTE_CURSOR_H
#define WIIMOTE_CURSOR_H

#include "sprites/ImageSprite.h"

class WiimoteCursor : public Graphics::ImageSprite
{
public:
    WiimoteCursor(int wiimoteIndex);

    virtual Vector2 GetPosition() const override;

    virtual void Render() override;
private:
    static const uint8_t* GetImageByChannel(int channel);
    static u32 GetPlayerColor(int player_index);

    static constexpr uint32_t SPRITE_COLOR = 0xFFFFFFFF;

    int m_wiimoteIndex;
    Vector2 m_lastValidPosition{0, 0};
};

#endif // WIIMOTE_CURSOR_H