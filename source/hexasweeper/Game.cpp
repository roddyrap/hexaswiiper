#include "Game.h"

#include <cmath>

using namespace Hexasweeper;

Hexasweeper::Game::Game(std::shared_ptr<::Graphics::Font> font, Vector2 position, u32 num_rows, u32 num_columns, u32 num_bombs) :
    m_tile_renderer{font, 32},
    m_board{num_rows, num_columns, num_bombs},
    m_position{position},
    m_game_start_time{}
{}

void Hexasweeper::Game::RevealTile(Vector2 screen_point)
{
    Vector2Int coordinates = this->PointToCoordinates(screen_point);
    if (!m_board.IsCoordinateInBoard(coordinates)) return;

    const Hexasweeper::Logic::TileState tile_state = m_board.GetTileState(coordinates);
    std::vector<Vector2Int> changed_tiles{};

    // Mimic left click - regular click that reveals hidden tiles.
    if (!tile_state.is_revealed)
    {
        changed_tiles = m_board.RevealTile(coordinates);
    }

    // Don't start the timer if no tiles have changed (Invalid clicks).
    if (m_game_start_time == 0 && changed_tiles.size() > 0)
    {
        // TODO: See if there are good monotonic options.
        m_game_start_time = time(nullptr);
    }

    // If the number of flags nearby is equal to the number of bombs nearby, reveal all nearby tiles.
    else if (!tile_state.is_flagged && tile_state.bombs_nearby > 0 && tile_state.bombs_nearby == m_board.NearbyFlags(coordinates))
    {
        for (const auto& tile : m_board.GetNeighbores(coordinates))
        {
            std::vector<Vector2Int> current_changed = m_board.RevealTile(tile);
            changed_tiles.insert(
                changed_tiles.end(),
                std::make_move_iterator(current_changed.begin()),
                std::make_move_iterator(current_changed.end())
            );
        }
    }
}

// TODO: Disallow flag before first click.
void Hexasweeper::Game::FlagTile(Vector2 screen_point)
{
    Vector2Int coordinates = this->PointToCoordinates(screen_point);
    if (!m_board.IsCoordinateInBoard(coordinates)) return;
    m_board.FlagTile(coordinates);
}

u32 Hexasweeper::Game::GetFlagsLeft() const
{
    return m_board.GetFlagsLeft();
}

u32 Hexasweeper::Game::GetNumBombs() const
{
    return m_board.GetNumBombs();
}

u64 Hexasweeper::Game::GetStartTime() const
{
    return m_game_start_time;
}

// Graphics stuff.
Vector2 Hexasweeper::Game::GetPosition() const
{
    return m_position;
}

void Hexasweeper::Game::Render()
{
    const RectangleBounds screen_rect{0, 0, static_cast<float>(rmode->fbWidth), static_cast<float>(rmode->efbHeight)};
    RectangleBounds draw_rect = screen_rect;
    if (m_clip_rect.has_value())
    {
        draw_rect = screen_rect.Intersection(*m_clip_rect);

        // If there is no intersection between the clip rect and the screen completely cull the tilemap.
        if (draw_rect.GetSize().x <= 0 || draw_rect.GetSize().y <= 0)
        {
            return;
        }

        GX_SetScissor(
            draw_rect.GetLeft(),
            draw_rect.GetTop(),
            draw_rect.GetSize().x,
            draw_rect.GetSize().y
        );
    }

    Vector2Int top_left = this->PointToCoordinates(draw_rect.GetTopLeft());
    Vector2Int bottom_right = this->PointToCoordinates(draw_rect.GetBottomRight());

    // Take +-1 offsets from the top left and bottom right to counter screen incosistencies.
    for (int16_t current_x = top_left.x - 1; current_x <= bottom_right.x + 1; ++current_x)
    {
        for (int16_t current_y = top_left.y - 1; current_y <= bottom_right.y + 1; ++current_y)
        {
            Vector2Int coordinates{current_x, current_y};
            if (!m_board.IsCoordinateInBoard(coordinates)) continue;

            Hexasweeper::Logic::TileState tile_state = m_board.GetTileState(coordinates);

            Vector2 tile_center{this->CalculatePosition(coordinates)};
            m_tile_renderer.DrawTile(tile_center, tile_state);
        }
    }

    // Reset the scissor to what I assume is the default.
    if (m_clip_rect.has_value())
    {
        GX_SetScissor(
            screen_rect.GetLeft(),
            screen_rect.GetTop(),
            screen_rect.GetSize().x,
            screen_rect.GetSize().y
        );
    }
}

void Hexasweeper::Game::SetTopLeft(Vector2 position)
{
    uint32_t radius{m_tile_renderer.GetHexagonRadius()};
    const Vector2 tile_size{std::sqrt(3.0f) * radius, 2.0f * radius};

    m_position = position + Vector2{tile_size.x / 2.0f, tile_size.y / 2.0f};
}

void Hexasweeper::Game::Move(Vector2 difference)
{
    m_position += difference;
}

Vector2Int Hexasweeper::Game::PointToCoordinates(Vector2 point)
{
    Vector2 distance = point - m_position;

    // Calculate floating Cube coordinates.
    float q_float = (std::sqrt(3.0f)/3.0f * distance.x - 1.0f/3 * distance.y) / m_tile_renderer.GetHexagonRadius();
    float r_float = (2.0f/3 * distance.y) / m_tile_renderer.GetHexagonRadius();
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

Vector2 Hexasweeper::Game::CalculatePosition(Vector2Int coordinates)
{
    Vector2 hexagonalPosition{};
    Vector2 origin = m_position;

    if (coordinates.y % 2 == 1)
    {
        origin.x += std::sqrt(3.0f) * m_tile_renderer.GetHexagonRadius() / 2.0f;
    }

    hexagonalPosition.x = origin.x + std::sqrt(3.0f) * m_tile_renderer.GetHexagonRadius() * coordinates.x;
    hexagonalPosition.y = origin.y + 1.5f * m_tile_renderer.GetHexagonRadius() * coordinates.y;

    return hexagonalPosition;
}

void Hexasweeper::Game::SetClipRect(std::optional<RectangleBounds> clip_rect)
{
    m_clip_rect = clip_rect;
}

std::optional<RectangleBounds> Hexasweeper::Game::GetClipRect() const
{
    return m_clip_rect;
}

std::optional<bool> Hexasweeper::Game::IsGameOver() const
{
    return m_board.IsGameOver();
}
