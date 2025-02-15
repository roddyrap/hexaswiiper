#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

namespace Graphics
{
    struct Vector2
    {
        Vector2() = default;
        explicit Vector2(float x) : x{x} {}
        Vector2(float x, float y) : x{x}, y{y} {};

        float x{};
        float y{};
    };

    struct Vector2Int
    {
        Vector2Int() = default;
        explicit Vector2Int(int x) : x{x} {}
        Vector2Int(int x, int y) : x{x}, y{y} {}

        int x{};
        int y{};
    };

    class RectangleBounds
    {
    public:
        RectangleBounds(Vector2 topLeft, Vector2 size) : m_topLeft{topLeft}, m_size{size} {}
        float GetRight();
        float GetLeft();
        float GetTop();
        float GetBottom();

        Vector2 GetTopLeft();
        Vector2 GetTopRight();
        Vector2 GetBottomLeft();
        Vector2 GetBottomRight();

        Vector2 GetSize();

    private:
        Vector2 m_topLeft;
        Vector2 m_size;
    };
}

#endif // GRAPHICS_UTILS_H