#ifndef GRAPHICS_SHAPES_H
#define GRAPHICS_SHAPES_H

#include <gctypes.h>
#include "common/Vector2.h"
#include "graphics/RectangleBounds.h"

namespace Graphics
{
    // Hexagons.
    void Draw_Hexagon(f32 xpos, f32 ypos, f32 radius, f32 start_angle, u32 color, bool filled);
    void Draw_PointyHexagon(f32 xpos, f32 ypos, f32 radius, u32 color, bool filled);
    void Draw_FlatHexagon(f32 xpos, f32 ypos, f32 radius, u32 color, bool filled);

    // Circles / Elipses.
    void  Draw_SemiCircle(const f32 x, const f32 y, const f32 radius, const u32 color,
                          const bool filled, int start_angle, int end_angle);

    // Rounded rectangles.
    void Draw_RoundedRectangle(f32 xpos, f32 ypos, f32 width, f32 height, f32 border_radius, u32 color, bool filled);
    void Draw_RoundedRectangle(RectangleBounds rect, f32 border_radius, u32 color, bool filled);
}

#endif // GRAPHICS_SHAPES_H