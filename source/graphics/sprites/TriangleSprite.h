#ifndef GRAPHICS_SPRITES_TRIANGLE_SPRITE_H
#define GRAPHICS_SPRITES_TRIANGLE_SPRITE_H

#include "RectSprite.h"
#include <array>

namespace Graphics
{
    class TriangleSprite : public RectSprite
    {
    public:
        // Create equilateral triangles.
        TriangleSprite(Vector2 triangle_center, int radius, uint32_t color, int rotation, bool filled);
        void Render() override;

        bool IsPositionHovering(Vector2 position) const override;

        int GetRotation() const;

        void SetPosition(Vector2 position) override;
        void SetCenter(Vector2 center);
        void SetRotation(int rotation);

    private:
        // Thanks to: https://stackoverflow.com/a/2049593
        static float sign(Vector2 p1, Vector2 p2, Vector2 p3);
        bool PointInTriangle(Vector2 point) const;

        void RecalculatePoints();

    private:
        std::array<Vector2, 3> m_points;
        int m_rotation;
        int m_radius;

        Vector2 m_triangle_center;
    };
}

#endif // GRAPHICS_SPRITES_TRIANGLE_SPRITE_H