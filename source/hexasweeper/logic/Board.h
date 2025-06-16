#ifndef HEXASWEEPER_BOARD_H
#define HEXASWEEPER_BOARD_H

#include <unordered_map>
#include <vector>
#include <optional>
#include <algorithm>
#include <gctypes.h>

#include "common/Vector2.h"

namespace Hexasweeper::Logic
{
    struct TileState {
        bool is_revealed{false};
        bool is_bomb{false};
        bool is_flagged{false};
        u8 bombs_nearby{0};
    };

    class Board
    {
    public:
        Board(u32 num_rows, u32 num_columns, u32 num_bombs);

        // Returns a vector of the coordinates that need to be redrawn.
        std::vector<Vector2Int> RevealTile(Vector2Int coordinates);

        // Returns true if a flag was placed/removed.
        bool FlagTile(Vector2Int coordinates);

        bool IsCoordinateInBoard(Vector2Int coordinates);

        std::optional<bool> IsGameOver();

        const TileState& GetTileState(Vector2Int coordinates) const;
        const u8 NearbyFlags(Vector2Int coordinates);

        std::vector<Vector2Int> GetNeighbores(Vector2Int originTile);

        // Game Information.
        u32 GetFlagsLeft() const;
        u32 GetNumBombs() const;
    private:
        void InitializeBombs(Vector2Int protected_center);


    private:
        std::unordered_map<Vector2Int, TileState> m_tiles;

        u32 m_num_rows;
        u32 m_num_columns;
        u32 m_num_bombs;

        bool m_initialized_bombs{false};
        u32 m_unflagged_bombs;
        u32 m_num_flags;

        bool m_clicked_on_bomb{false};
    };
}

#endif // HEXASWEEPER_BOARD_H