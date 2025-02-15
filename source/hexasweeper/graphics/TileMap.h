#ifndef HEXASWEEPER_TILEMAP_H
#define HEXASWEEPER_TILEMAP_H

#include "common/Vector2.h"
#include "TileSprite.h"

#include <tgmath.h>
#include <unordered_map>

namespace Hexasweeper::Graphics
{
    class Tilemap : public ::Graphics::Sprite
    {
    public:
        Tilemap(Vector2 position, u32 hexagon_radius = 32) :
            m_tiles{}, m_position{position}, m_hexagon_radius{hexagon_radius} {}

        void CreateTile(Vector2Int coordinates)
        {
            Vector2 tile_position = this->CalculatePosition(coordinates);
            m_tiles.emplace(std::make_pair(coordinates, TileSprite{tile_position.x, tile_position.y, m_hexagon_radius}));
        }

        virtual Vector2 GetPosition() override
        {
            return m_position;
        }

        virtual void Render() override
        {
            for (auto& tile : m_tiles)
            {
                tile.second.Render();
            }
        }


    private:
        Vector2 CalculatePosition(Vector2Int coordinates)
        {
            Vector2 hexagonalPosition;
            Vector2 origin = this->GetPosition();

            if (coordinates.y % 2 == 1)
            {
                origin.x += std::sqrt(3.0f) * m_hexagon_radius / 2.0f;
            }

            hexagonalPosition.x = origin.x + std::sqrt(3.0f) * m_hexagon_radius * coordinates.x;
            hexagonalPosition.y = origin.y + 1.5f * m_hexagon_radius * coordinates.y;

            return hexagonalPosition;
        }

    private:
        std::unordered_map<Vector2Int, TileSprite> m_tiles;
        Vector2 m_position;
        u32 m_hexagon_radius;
    };
}

#endif // HEXASWEEPER_TILEMAP_H