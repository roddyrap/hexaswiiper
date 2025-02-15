#ifndef HEXASWEEPER_TILEMAP_H
#define HEXASWEEPER_TILEMAP_H

#include "common/Vector2.h"
#include "TileSprite.h"

#include <tgmath.h>
#include <unordered_map>

using ::Graphics::RectangleBounds;

namespace Hexasweeper::Graphics
{
    class Tilemap : public ::Graphics::Sprite
    {
    public:
        Tilemap(Vector2 position, u32 hexagon_radius = 32);

        void CreateTile(Vector2Int coordinates);
        void SetTile(Vector2Int coordinates, TileSprite&& sprite);

        void SetTopLeft(Vector2 position);
        void Move(Vector2 difference);

        virtual Vector2 GetPosition() override;

        virtual void Render() override;

        Vector2Int PointToCoordinates(Vector2 point);

        Vector2 CalculatePosition(Vector2Int coordinates);

        u32 GetHexagonRadius() const;

        RectangleBounds GetBounds();
    private:
        void UpdateBounds(Vector2Int new_coordinates);

    private:
        std::unordered_map<Vector2Int, TileSprite> m_tiles;
        Vector2 m_position;
        u32 m_hexagon_radius;

        RectangleBounds m_bounds;
    };
}

#endif // HEXASWEEPER_TILEMAP_H