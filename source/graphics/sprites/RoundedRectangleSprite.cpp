#include "RoundedRectangleSprite.h"

#include "graphics/Shapes.h"

namespace Graphics
{
    void RoundedRectangleSprite::Render()
    {
        Draw_RoundedRectangle(m_position.x, m_position.y, m_size.x, m_size.y, m_border_radius, m_color, this->GetFill());
    }
}
