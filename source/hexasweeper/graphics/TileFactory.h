#ifndef HEXASWEEPER_GRAPHICS_TILE_FACTORY_H
#define HEXASWEEPER_GRAPHICS_TILE_FACTORY_H

#include <array>
#include <memory>

#include "graphics/text/Font.h"
#include "TileSprite.h"

namespace Hexasweeper::Graphics
{
    constexpr u32 TILE_FONT_SIZE = 35;

    constexpr std::array <u32, 6> NEARBY_COLORS{
        RGBA(0, 0, 255, 255),
        RGBA(0, 127, 14, 255),
        RGBA(255, 0, 0, 255),
        RGBA(0, 19, 127, 255),
        RGBA(127, 0, 0, 255),
        RGBA(0, 148, 255, 255)
    };

    TileHexSprite CreateHiddenHexSprite(Vector2 position, u32 radius);

    TileHexSprite CreateRevealedHexSprite(Vector2 position, u32 radius);

    TileSprite CreateTile(Vector2 position, u32 radius, bool revealed, std::unique_ptr<::Graphics::RectSprite> inner_sprite);

    TileSprite CreateHiddenTile(Vector2 position, u32 radius);

    // Empty tile.
    TileSprite CreateRevealedTile(Vector2 position, u32 radius);

    TileSprite CreateBombTile(Vector2 position, u32 radius);

    TileSprite CreateFlagTile(Vector2 position, u32 radius);

    TileSprite CreateNearbyTile(std::shared_ptr<::Graphics::Font> font, u8 num_nearby, Vector2 position, u32 radius);
}

#endif // HEXASWEEPER_GRAPHICS_TILE_FACTORY_H