#include "sprites/ImageSprite.h"

class WiimoteCursor : public Graphics::RectSprite
{
public:
    WiimoteCursor(int wiimoteIndex);

    virtual Graphics::Vector2 GetPosition() override;

private:
    static const uint8_t* GetImageByChannel(int channel);

    static constexpr uint32_t SPRITE_COLOR = 0xFFFFFFFF;

    int m_wiimoteIndex;
    Graphics::Vector2 m_lastValidPosition{0, 0};
};