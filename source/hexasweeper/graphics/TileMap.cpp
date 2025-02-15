#include "TileMap.h"

Hexasweeper::Graphics::Tilemap::Tilemap(Vector2 position, u32 hexagon_radius) :
    m_tiles{}, m_position{position}, m_hexagon_radius{hexagon_radius} {}

void Hexasweeper::Graphics::Tilemap::CreateTile(Vector2Int coordinates)
{
    Vector2 tile_position = this->CalculatePosition(coordinates);
    m_tiles.emplace(std::make_pair(coordinates, TileSprite{tile_position.x, tile_position.y, m_hexagon_radius}));
}


void Hexasweeper::Graphics::Tilemap::SetTile(Vector2Int coordinates, TileSprite&& sprite)
{
    const auto map_iter = m_tiles.find(coordinates);
    if (map_iter != m_tiles.end())
    {
        m_tiles.erase(map_iter);
    }

    m_tiles.insert(std::pair<Vector2Int, TileSprite>{coordinates, std::move(sprite)});
}

Vector2 Hexasweeper::Graphics::Tilemap::GetPosition()
{
    return m_position;
}

void Hexasweeper::Graphics::Tilemap::Render()
{
    for (auto& tile : m_tiles)
    {
        tile.second.Render();
    }
}

Vector2Int Hexasweeper::Graphics::Tilemap::PointToCoordinates(Vector2 point)
{
    Vector2 distance = point - this->GetPosition();

    // Calculate floating Cube coordinates.
    float q_float = (std::sqrt(3.0f)/3.0f * distance.x - 1.0f/3 * distance.y) / m_hexagon_radius;
    float r_float = (2.0f/3 * distance.y) / m_hexagon_radius;
    float s_float = - (q_float + r_float);

    // Round floating cube coordniates.
    int q = static_cast<int>(std::round(q_float));
    int r = static_cast<int>(std::round(r_float));
    int s = static_cast<int>(std::round(s_float));

    float q_diff = std::abs(q - q_float);
    float r_diff = std::abs(r - r_float);
    float s_diff = std::abs(s - s_float);

    if (q_diff > r_diff && q_diff > s_diff) {
        q = -r-s;
    }
    else if (r_diff > s_diff) {
        r = -q-s;
    }
    else
    {
        s = -q-r;
    }

    // Convert cube coordinates to offset coordinates.
    int col = q + (r - (r & 1)) / 2;
    int row = r;

    return Vector2Int{col, row};
}

Vector2 Hexasweeper::Graphics::Tilemap::CalculatePosition(Vector2Int coordinates)
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

u32 Hexasweeper::Graphics::Tilemap::GetHexagonRadius() const
{
    return m_hexagon_radius;
}