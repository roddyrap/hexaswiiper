#ifndef HEXASWEEPER_LOGIC_DIFFICULTY_H
#define HEXASWEEPER_LOGIC_DIFFICULTY_H

#include "common/Vector2.h"

#include <stdint.h>
#include <string>
#include <array>

namespace Hexasweeper
{
    struct Difficulty
    {
        std::string name;
        Vector2Int board_size;
        uint16_t num_bombs;
    };

    constexpr Difficulty TEST_DIFFICULTY{ .name = "Testing", .board_size = Vector2Int{10, 10}, .num_bombs = 3};

    constexpr std::array<Difficulty, 4> DIFFICULTIES{
        Difficulty{ .name = "Easy",         .board_size = Vector2Int{15, 15}, .num_bombs = 27},
        Difficulty{ .name = "Intermediate", .board_size = Vector2Int{24, 24}, .num_bombs = 80},
        Difficulty{ .name = "Hard",         .board_size = Vector2Int{35, 35}, .num_bombs = 180},
        Difficulty{ .name = "Nightmare",    .board_size = Vector2Int{60, 60}, .num_bombs = 540}
    };
}

#endif // HEXASWEEPER_LOGIC_DIFFICULTY_H