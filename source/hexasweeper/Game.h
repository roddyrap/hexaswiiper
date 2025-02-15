#ifndef HEXASWEEPER_GAME_H
#define HEXASWEEPER_GAME_H

#include "logic/Board.h"
#include "graphics/TileMap.h"

namespace Hexasweeper
{
    class Game
    {
    public:
        Game(Vector2 position, u32 num_rows, u32 num_columns, u32 num_bombs);

        Graphics::Tilemap& GetTilemap();

    private:
        Logic::Board m_board;
        Graphics::Tilemap m_tilemap;
    };
}

#endif // HEXASWEEPER_GAME_H