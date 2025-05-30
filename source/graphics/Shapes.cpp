#include "Shapes.h"

#include "common/Math.h"
#include <tgmath.h>
#include <ogc/gx.h>
#include <ogc/system.h>


using namespace Graphics;

void Graphics::Draw_Hexagon(f32 xpos, f32 ypos, f32 radius, f32 start_angle, u32 color)
{
    GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 8);
        GX_Position3f32(xpos, ypos, 0.0f);
        GX_Color1u32(color);

        for (f32 degree_angle = start_angle; degree_angle <= start_angle + 360.0; degree_angle += 360.0 / 6.0)
        {
            f32 rad_angle = DegreesToRadians(degree_angle);
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

void  Graphics::Draw_SemiCircle(const f32 x, const f32 y, const f32 radius, const u32 color,
                                const bool filled, int start_angle, int end_angle) {
    Vector2 center{x, y};
    Vector2 start{center + PolarToCartesian(radius, start_angle)};
    Vector2 end{center + PolarToCartesian(radius, end_angle)};

    // Normalize the degrees in order to get the absolute length of the perimiter that
    // should be created. Most notably deal with negative degrees and over 360.
    start_angle = NormalizeAngle(start_angle);
    end_angle = NormalizeAngle(end_angle);

    int angle_diff = end_angle - start_angle;
    if (angle_diff <= 0) angle_diff += 360;

    // The number of dots that are used for the line in a full circle (Pretty much number of lines).
    // GRRLIB_DrawEllipse uses 36 points, but I have encountered some rounding issues that harm the
    // display (Most notably: 9 points for 0 to 90 semicircle of radius 5 doesn't render correctly).
    constexpr int FULL_CIRCLE_PRECISION = 40;

    int num_points = std::round(FULL_CIRCLE_PRECISION / (360.0 / static_cast<float>(angle_diff)));
    SYS_Report("Center: (x: %f, y: %f), Start: %d, End: %d => Diff: %d. Num points: %d\n", x, y, start_angle, end_angle, angle_diff, num_points);
    if (num_points == 0) return;
    else if (num_points == 1) {
        GX_Begin(GX_POINTS, 0, 1);
            Vector2 position = center + PolarToCartesian(radius, start_angle);
            GX_Position3f32(position.x, position.y, 0);
            GX_Color1u32(color);
        GX_End();
        return;
    }

    uint8_t gx_primitive = filled ? GX_TRIANGLEFAN : GX_LINESTRIP;

    // Add a point for the circle center, in order to constrct the triangles with a shared point.
    GX_Begin(gx_primitive, GX_VTXFMT0, num_points + filled);
        if (filled)
        {
            GX_Position3f32(center.x, center.y, 0.0f);
            GX_Color1u32(color);
            SYS_Report("Triangle point: (x: %f, y: %f)\n", center.x, center.y);
        }

        for (const auto& current_angle : linspace(start_angle, start_angle + angle_diff, num_points))
        {
            Vector2 position = center + PolarToCartesian(radius, current_angle);
            GX_Position3f32(position.x, position.y, 0.0f);
            GX_Color1u32(color);
            SYS_Report("Semicircle point: Theta: %lf, (x: %f, y: %f)\n", current_angle, position.x, position.y);
        }
    GX_End();
}

void Graphics::Draw_RoundedRectangle(f32 xpos, f32 ypos, f32 width, f32 height, f32 border_radius, u32 color, bool filled)
{
    // Draw straight lines.
    // TODO: Handle if width/height is smaller than border_radius * 2.
    f32 inner_top = ypos + border_radius;
    f32 inner_bottom = ypos + height - border_radius;
    f32 inner_left = xpos + border_radius;
    f32 inner_right = xpos + width - border_radius;

    int num_points = 8;
    uint8_t gx_primitive = GX_LINES;
    if (filled)
    {
        gx_primitive = GX_TRIANGLEFAN;
        num_points += 6;
    }
    GX_Begin(gx_primitive, GX_VTXFMT0, num_points);
        if (filled)
        {
            // All that is needed is a point in the rectangle, so take the middle.
            GX_Position3f32(xpos + width / 2.0, ypos + height / 2.0, 0.0f);
            GX_Color1u32(color);
        }

        GX_Position3f32(xpos, inner_top, 0.0f);
        GX_Color1u32(color);
        GX_Position3f32(xpos, inner_bottom, 0.0f);
        GX_Color1u32(color);
        if (filled)
        {
            GX_Position3f32(inner_left, inner_bottom, 0.0f);
            GX_Color1u32(color);
        }

        GX_Position3f32(inner_left, ypos + height, 0.0f);
        GX_Color1u32(color);
        GX_Position3f32(inner_right, ypos + height, 0.0f);
        GX_Color1u32(color);
        if (filled)
        {
            GX_Position3f32(inner_right, inner_bottom, 0.0f);
            GX_Color1u32(color);
        }

        GX_Position3f32(xpos + width, inner_bottom, 0.0f);
        GX_Color1u32(color);
        GX_Position3f32(xpos + width, inner_top, 0.0f);
        GX_Color1u32(color);
        if (filled)
        {
            GX_Position3f32(inner_right, inner_top, 0.0f);
            GX_Color1u32(color);
        }

        GX_Position3f32(inner_right, ypos, 0.0f);
        GX_Color1u32(color);
        GX_Position3f32(inner_left, ypos, 0.0f);
        GX_Color1u32(color);
        if (filled)
        {
            GX_Position3f32(inner_left, inner_top, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(xpos, inner_top, 0.0f);
            GX_Color1u32(color);
        }
    GX_End();

    // Draw corners.

    // Bottom Right.
    Draw_SemiCircle(inner_right, inner_bottom, border_radius, color, filled, 0, 90);

    // Bottom Left.
    Draw_SemiCircle(inner_left, inner_bottom, border_radius, color, filled, 90, 180);

    // Top Left.
    Draw_SemiCircle(inner_left, inner_top, border_radius, color, filled, 180, 270);

    // Top Right.
    Draw_SemiCircle(inner_right, inner_top, border_radius, color, filled, 270, 360);
}
