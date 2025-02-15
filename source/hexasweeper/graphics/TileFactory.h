#ifndef HEXASWEEPER_GRAPHICS_TILE_FACTORY_H
#define HEXASWEEPER_GRAPHICS_TILE_FACTORY_H

#include <memory>

#include "TileSprite.h"

namespace Hexasweeper::Graphics
{
    TileSprite CreateHiddenTile(Vector2 position, u32 radius);

    // Empty tile.
    TileSprite CreateRevealedTile(Vector2 position, u32 radius);

    TileSprite CreateBombTile(Vector2 position, u32 radius);

    TileSprite CreateFlagTile(Vector2 position, u32 radius);

    TileSprite CreateNearbyTile(std::shared_ptr<GRRLIB_ttfFont> font, u8 num_nearby, Vector2 position, u32 radius);
}

#endif // HEXASWEEPER_GRAPHICS_TILE_FACTORY_H