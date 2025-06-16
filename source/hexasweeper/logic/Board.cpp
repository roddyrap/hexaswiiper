#include "Board.h"

Hexasweeper::Logic::Board::Board(u32 num_rows, u32 num_columns, u32 num_bombs) : m_tiles{}, m_num_rows{num_rows}, m_num_columns{num_columns}, m_num_bombs{num_bombs}, m_unflagged_bombs{num_bombs}, m_num_flags{num_bombs}
{
    for (u32 row_index = 0; row_index < num_rows; ++row_index)
    {
        for (u32 column_index = 0; column_index < num_columns; ++column_index)
        {
            Vector2Int tile_coordinates{static_cast<int>(column_index), static_cast<int>(row_index)};
            m_tiles.emplace(std::pair<Vector2Int, TileState>{tile_coordinates, TileState{}});
        }
    }
}

std::vector<Vector2Int> Hexasweeper::Logic::Board::RevealTile(Vector2Int coordinates)
{
    TileState& tile_state = m_tiles[coordinates];
    if (tile_state.is_revealed || tile_state.is_flagged) return {};
    if (!m_initialized_bombs) InitializeBombs(coordinates);

    std::vector<Vector2Int> redrawn_tiles{coordinates};
    tile_state.is_revealed = true;
    if (tile_state.is_bomb) m_clicked_on_bomb = true;

    if (!tile_state.is_bomb && tile_state.bombs_nearby == 0)
    {
        for (auto& neighboour : GetNeighbores(coordinates))
        {
            std::vector<Vector2Int> new_redrawn_tiles = this->RevealTile(neighboour);

            // Concatenate new_redrawn_tiles with redrawn_tiles.
            redrawn_tiles.insert(
                redrawn_tiles.end(),
                std::make_move_iterator(new_redrawn_tiles.begin()),
                std::make_move_iterator(new_redrawn_tiles.end())
            );
        }
    }

    return redrawn_tiles;
}

bool Hexasweeper::Logic::Board::FlagTile(Vector2Int coordinates)
{
    TileState& tile_state = m_tiles[coordinates];
    if (tile_state.is_revealed) return false;
    if (tile_state.is_flagged)
    {
        ++m_num_flags;
        m_unflagged_bombs += tile_state.is_bomb;
        tile_state.is_flagged = false;
    }
    else
    {
        // Not enough flags.
        if (m_num_flags <= 0) return false;
        --m_num_flags;

        m_unflagged_bombs -= tile_state.is_bomb;

        tile_state.is_flagged = true;
    }

    return true;
}

bool Hexasweeper::Logic::Board::IsCoordinateInBoard(Vector2Int coordinates)
{
    return m_tiles.contains(coordinates);
}

std::optional<bool> Hexasweeper::Logic::Board::IsGameOver()
{
    if (m_clicked_on_bomb) return false;
    if (m_unflagged_bombs == 0) return true;

    return std::nullopt;
}

const Hexasweeper::Logic::TileState& Hexasweeper::Logic::Board::GetTileState(Vector2Int coordinates) const
{
    return m_tiles.at(coordinates);
}

const u8 Hexasweeper::Logic::Board::NearbyFlags(Vector2Int coordinates)
{
    u8 nearby_flags = 0;
    for (auto& tile : GetNeighbores(coordinates))
    {
        nearby_flags += m_tiles[tile].is_flagged;
    }

    return nearby_flags;
}

u32 Hexasweeper::Logic::Board::GetFlagsLeft() const
{
    return m_num_flags;
}

u32 Hexasweeper::Logic::Board::GetNumBombs() const
{
    return m_num_bombs;
}

void Hexasweeper::Logic::Board::InitializeBombs(Vector2Int protected_center)
{
    m_initialized_bombs = true;

    std::vector<Vector2Int> protected_coordinates{this->GetNeighbores(protected_center)};
    protected_coordinates.push_back(protected_center);

    // Using reservoir sampling in order to generate the bombs locations.
    std::vector<Vector2Int> bomb_positions;
    u32 tile_index = 0;
    for (auto& tile_iterator : m_tiles)
    {
        if (std::find(protected_coordinates.cbegin(), protected_coordinates.cend(), tile_iterator.first) != protected_coordinates.cend())
        {
            continue;
        }

        if (bomb_positions.size() < m_num_bombs)
        {
            bomb_positions.push_back(tile_iterator.first);
        }
        else
        {
            // Replacing it with a previously in number.
            u32 generated_index = rand() % tile_index;
            if (generated_index < m_num_bombs)
            {
                bomb_positions[generated_index] = tile_iterator.first;
            }
        }

        ++tile_index;
    }

    for (const auto& bomb_position : bomb_positions)
    {
        m_tiles[bomb_position].is_bomb = true;

        for (auto& bomb_neighbour : this->GetNeighbores(bomb_position))
        {
            ++m_tiles[bomb_neighbour].bombs_nearby;
        }
    }
}

std::vector<Vector2Int> Hexasweeper::Logic::Board::GetNeighbores(Vector2Int originTile)
{
    std::vector<Vector2Int> neighboures{};

    int otherLineOffset = originTile.y % 2 == 1 ? 1 : -1;

    std::array<Vector2Int, 6> possibleTiles{{
        {originTile.x - 1, originTile.y},
        {originTile.x + 1, originTile.y},
        {originTile.x, originTile.y - 1},
        {originTile.x, originTile.y + 1},
        {originTile.x + otherLineOffset, originTile.y - 1},
        {originTile.x + otherLineOffset, originTile.y + 1}
    }};

    for (const auto& tile : possibleTiles)
    {
        if (this->IsCoordinateInBoard(tile))
        {
            neighboures.emplace_back(tile);
        }
    }

    return neighboures;
}