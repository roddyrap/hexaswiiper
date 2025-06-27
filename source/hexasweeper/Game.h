#ifndef HEXASWEEPER_GAME_H
#define HEXASWEEPER_GAME_H

#include "logic/Board.h"
#include "graphics/text/Font.h"
#include "graphics/Sprite.h"
#include "graphics/RectangleBounds.h"

#include "hexasweeper/TileRenderer.h"

namespace Hexasweeper
{
    using ::Graphics::RectangleBounds;

    class Game : ::Graphics::Sprite
    {
    public:
        Game(std::shared_ptr<::Graphics::Font> font, Vector2 position, u32 num_rows, u32 num_columns, u32 num_bombs);

        void RevealTile(Vector2 screen_point);
        void FlagTile(Vector2 screen_point);

        u32 GetFlagsLeft() const;
        u32 GetNumBombs() const;
        u64 GetStartTime() const;

        // Graphics stuff.
        Vector2 GetPosition() const override;

        void Render() override;

        void SetTopLeft(Vector2 position);
        void Move(Vector2 difference);

        Vector2Int PointToCoordinates(Vector2 point);
        Vector2 CalculatePosition(Vector2Int coordinates);

        void SetClipRect(std::optional<RectangleBounds> clip_rect);
        std::optional<RectangleBounds> GetClipRect() const;

        std::optional<bool> IsGameOver() const;

    private:
        TileRenderer m_tile_renderer;
        Logic::Board m_board;

        Vector2 m_position;

        u64 m_game_start_time;

        std::optional<RectangleBounds> m_clip_rect{std::nullopt};
    };
}

#endif // HEXASWEEPER_GAME_H