#include "Game.h"

#include "graphics/TileFactory.h"

Hexasweeper::Game::Game(std::shared_ptr<::Graphics::TTFFont> font, Vector2 position, u32 num_rows, u32 num_columns, u32 num_bombs) : m_font{font}, m_board{num_rows, num_columns, num_bombs}, m_tilemap{position}
{
    for (u32 row_index = 0; row_index < num_rows; ++row_index)
    {
        for (u32 column_index = 0; column_index < num_columns; ++column_index)
        {
            m_tilemap.CreateTile({column_index, row_index});
        }
    }
}

void Hexasweeper::Game::RevealTile(Vector2 screen_point)
{
    Vector2Int coordinates = m_tilemap.PointToCoordinates(screen_point);
    if (!m_board.IsCoordinateInBoard(coordinates)) return;

    std::vector<Vector2Int> changed_tiles = m_board.RevealTile(coordinates);
    for (auto& tile_coordinates : changed_tiles)
    {
        m_tilemap.SetTile(tile_coordinates, CreateTileSprite(tile_coordinates));
    }
}

void Hexasweeper::Game::FlagTile(Vector2 screen_point)
{
    Vector2Int coordinates = m_tilemap.PointToCoordinates(screen_point);
    if (!m_board.IsCoordinateInBoard(coordinates)) return;

    if (!m_board.FlagTile(coordinates)) return;

    m_tilemap.SetTile(coordinates, CreateTileSprite(coordinates));
}

Hexasweeper::Graphics::Tilemap& Hexasweeper::Game::GetTilemap()
{
    return m_tilemap;
}

Hexasweeper::Graphics::TileSprite Hexasweeper::Game::CreateTileSprite(Vector2Int coordinates)
{
    const Hexasweeper::Logic::TileState &tile_state = m_board.GetTileState(coordinates);
    Vector2 position = m_tilemap.CalculatePosition(coordinates);
    u32 hexagon_radius = m_tilemap.GetHexagonRadius();

    if (tile_state.is_flagged) return Hexasweeper::Graphics::CreateFlagTile(position, hexagon_radius);
    if (!tile_state.is_revealed) return Hexasweeper::Graphics::CreateHiddenTile(position, hexagon_radius);
    if (tile_state.is_bomb) return Hexasweeper::Graphics::CreateBombTile(position, hexagon_radius);
    if (tile_state.bombs_nearby == 0) return Hexasweeper::Graphics::CreateRevealedTile(position, hexagon_radius);

    return Hexasweeper::Graphics::CreateNearbyTile(m_font, tile_state.bombs_nearby, position, hexagon_radius);
}