#ifndef HEXASWEEPER_GAME_H
#define HEXASWEEPER_GAME_H

#include "logic/Board.h"
#include "graphics/TileMap.h"
#include "graphics/text/Font.h"

namespace Hexasweeper
{
    class Game
    {
    public:
        Game(std::shared_ptr<::Graphics::Font> font, Vector2 position, u32 num_rows, u32 num_columns, u32 num_bombs);

        void RevealTile(Vector2 screen_point);
        void FlagTile(Vector2 screen_point);

        Graphics::Tilemap& GetTilemap();

    private:
        Graphics::TileSprite CreateTileSprite(Vector2Int coordinates);

    private:
        Logic::Board m_board;
        Graphics::Tilemap m_tilemap;

        std::shared_ptr<::Graphics::Font> m_font;
    };
}

#endif // HEXASWEEPER_GAME_H