#include "TileMap.h"

#include <tgmath.h>

Hexasweeper::Graphics::Tilemap::Tilemap(Vector2 position, u32 hexagon_radius) :
    m_tiles{}, m_hexagon_radius{hexagon_radius}, m_position{position}, m_clip_rect{std::nullopt} {}

void Hexasweeper::Graphics::Tilemap::CreateTile(Vector2Int coordinates)
{
    Vector2 tile_position = this->CalculatePosition(coordinates);
    this->SetTile(coordinates, TileSprite{tile_position.x, tile_position.y, m_hexagon_radius});
}


void Hexasweeper::Graphics::Tilemap::SetTile(Vector2Int coordinates, TileSprite&& sprite)
{
    const auto map_iter = m_tiles.find(coordinates);
    if (map_iter != m_tiles.end())
    {
        m_tiles.erase(map_iter);
    }

    m_tiles.insert(std::pair<Vector2Int, TileSprite>{coordinates, std::move(sprite)});
    this->UpdateBounds(coordinates);
}

void Hexasweeper::Graphics::Tilemap::SetTopLeft(Vector2 position)
{
    Vector2 difference = position - m_bounds.GetTopLeft();
    this->Move(difference);
}

void Hexasweeper::Graphics::Tilemap::Move(Vector2 difference)
{
    m_position = m_position + difference;
    m_bounds = ::Graphics::RectangleBounds{m_bounds.GetTopLeft() + difference, m_bounds.GetSize()};

    for (auto& tile : m_tiles)
    {
        tile.second.SetCenter(this->CalculatePosition(tile.first));
    }
}

Vector2 Hexasweeper::Graphics::Tilemap::GetPosition() const
{
    return m_position;
}

void Hexasweeper::Graphics::Tilemap::Render()
{
    if (m_clip_rect.has_value())
    {
        GX_SetScissor(m_clip_rect->GetLeft(), m_clip_rect->GetTop(), m_clip_rect->GetSize().x, m_clip_rect->GetSize().y);
    }

    for (auto& tile : m_tiles)
    {
        tile.second.Render();
    }

    // Reset the scissor to what I assume is the default.
    if (m_clip_rect.has_value())
    {
        GX_SetScissor(0,0,rmode->fbWidth,rmode->efbHeight);
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

RectangleBounds Hexasweeper::Graphics::Tilemap::GetBounds() const
{
    return m_bounds;
}

void Hexasweeper::Graphics::Tilemap::SetClipRect(std::optional<RectangleBounds> clip_rect)
{
    m_clip_rect = clip_rect;

}

void Hexasweeper::Graphics::Tilemap::ClearClipRect()
{
    SetClipRect(std::nullopt);
}

std::optional<RectangleBounds> Hexasweeper::Graphics::Tilemap::GetClipRect() const
{
    return m_clip_rect;
}

void Hexasweeper::Graphics::Tilemap::UpdateBounds(Vector2Int new_coordinates)
{
    Vector2 new_center = this->CalculatePosition(new_coordinates);

    // Check that both top-left and bottom-right are inside the bounds.
    Vector2 top_left = new_center - m_hexagon_radius;
    Vector2 bottom_right = new_center + m_hexagon_radius;

    m_bounds.UpdateToFit(top_left);
    m_bounds.UpdateToFit(bottom_right);
}
