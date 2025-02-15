#include "Game.h"

Hexasweeper::Game::Game(Vector2 position, u32 num_rows, u32 num_columns, u32 num_bombs) : m_board{num_rows, num_columns, num_bombs}, m_tilemap{position}
{
    for (u32 row_index = 0; row_index < num_rows; ++row_index)
    {
        for (u32 column_index = 0; column_index < num_columns; ++column_index)
        {
            m_tilemap.CreateTile({column_index, row_index});
        }
    }
}

Hexasweeper::Graphics::Tilemap& Hexasweeper::Game::GetTilemap()
{
    return m_tilemap;
}