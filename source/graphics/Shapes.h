#ifndef GRAPHICS_SHAPES_H
#define GRAPHICS_SHAPES_H

#include <gctypes.h>

namespace Graphics
{
    void Draw_Hexagon(f32 xpos, f32 ypos, f32 radius, f32 start_angle, u32 color);
    void Draw_PointyHexagon(f32 xpos, f32 ypos, f32 radius, u32 color);
    void Draw_FlatHexagon(f32 xpos, f32 ypos, f32 radius, u32 color);
}

#endif // GRAPHICS_SHAPES_H