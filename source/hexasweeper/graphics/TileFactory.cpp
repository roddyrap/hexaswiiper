#include "TileFactory.h"

#include "graphics/sprites/ImageSprite.h"
#include "graphics/sprites/TextSprite.h"
#include "bomb_png.h"
#include "flag_png.h"

using namespace Hexasweeper::Graphics;
using namespace ::Graphics;

TileHexSprite Hexasweeper::Graphics::CreateHiddenHexSprite(Vector2 position, u32 radius)
{
    return TileHexSprite{position.x, position.y, radius, TileHexSprite::RIM_COLOR, TileHexSprite::MIDDLE_COLOR, TileHexSprite::HIDDEN_INTERNAL_COLOR};
}

TileHexSprite Hexasweeper::Graphics::CreateRevealedHexSprite(Vector2 position, u32 radius)
{
    return TileHexSprite{position.x, position.y, radius, TileHexSprite::RIM_COLOR, TileHexSprite::MIDDLE_COLOR, TileHexSprite::REVEALED_INTERNAL_COLOR};

}

TileSprite Hexasweeper::Graphics::CreateTile(Vector2 position, u32 radius, bool revealed, std::unique_ptr<::Graphics::RectSprite> inner_sprite)
{
    TileSprite tile_sprite = TileSprite{position.x, position.y, radius, std::move(inner_sprite)};
    tile_sprite.SetTileHexSprite(revealed ? CreateRevealedHexSprite(position, radius) : CreateHiddenHexSprite(position, radius));

    return tile_sprite;
}

TileSprite Hexasweeper::Graphics::CreateHiddenTile(Vector2 position, u32 radius)
{
    return CreateTile(position, radius, false, nullptr);
}

TileSprite Hexasweeper::Graphics::CreateRevealedTile(Vector2 position, u32 radius)
{
    return CreateTile(position, radius, true, nullptr);
}

TileSprite Hexasweeper::Graphics::CreateBombTile(Vector2 position, u32 radius)
{
    std::unique_ptr<ImageSprite> bomb_sprite = std::make_unique<ImageSprite>(bomb_png, Vector2{0.1, 0.1});
    bomb_sprite->SetCenter({position.x, position.y});

    return CreateTile(position, radius, true, std::move(bomb_sprite));
}

TileSprite Hexasweeper::Graphics::CreateFlagTile(Vector2 position, u32 radius)
{
    std::unique_ptr<ImageSprite> flag_sprite = std::make_unique<ImageSprite>(flag_png, Vector2{0.1, 0.1});
    flag_sprite->SetCenter(position);

    return CreateTile(position, radius, false, std::move(flag_sprite));

}

TileSprite Hexasweeper::Graphics::CreateNearbyTile(std::shared_ptr<::Graphics::Font> font, u8 num_nearby, Vector2 position, u32 radius)
{
    u32 color = UINT32_MAX;

    // num_nearby is 1-based but the colors are 0-based.
    if (num_nearby > 0 && num_nearby <= NEARBY_COLORS.size())
    {
        color = NEARBY_COLORS[num_nearby - 1];
    }

    std::string nearby_string = std::to_string(num_nearby);

    std::unique_ptr<TextSprite> number_sprite = std::make_unique<TextSprite>(Vector2{position.x, position.y}, font, nearby_string, TILE_FONT_SIZE, color);
    number_sprite->SetCenter({position.x, position.y});

    return CreateTile(position, radius, true, std::move(number_sprite));
}
