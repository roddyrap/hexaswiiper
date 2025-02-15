#include "Shapes.h"

#include <tgmath.h>
#include <ogc/gx.h>

#define PI 3.14159265

void Graphics::Draw_Hexagon(f32 xpos, f32 ypos, f32 radius, f32 start_angle, u32 color)
{
    GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 8);
        GX_Position3f32(xpos, ypos, 0.0f);
        GX_Color1u32(color);

        for (f32 degree_angle = start_angle; degree_angle <= start_angle + 360.0; degree_angle += 360.0 / 6.0)
        {
            f32 rad_angle = degree_angle * PI / 180;
            f32 new_xpos = xpos + radius * std::cos(rad_angle);
            f32 new_ypos = ypos + radius * std::sin(rad_angle);

            GX_Position3f32(new_xpos, new_ypos, 0.0f);
            GX_Color1u32(color);
        }
    GX_End();
}

void Graphics::Draw_PointyHexagon(f32 xpos, f32 ypos, f32 radius, u32 color)
{
    Draw_Hexagon(xpos, ypos, radius, 90.0, color);
}

void Graphics::Draw_FlatHexagon(f32 xpos, f32 ypos, f32 radius, u32 color)
{
    Draw_Hexagon(xpos, ypos, radius, 0.0, color);
}