#include "TileFactory.h"

#include "graphics/sprites/ImageSprite.h"
#include "graphics/sprites/TextSprite.h"
#include "bomb_png.h"
#include "flag_png.h"

using namespace Hexasweeper::Graphics;
using namespace ::Graphics;

TileSprite Hexasweeper::Graphics::CreateHiddenTile(Vector2 position, u32 radius)
{
    return TileSprite{position.x, position.y, radius};
}

TileSprite Hexasweeper::Graphics::CreateRevealedTile(Vector2 position, u32 radius)
{
    auto tile_sprite = TileSprite{position.x, position.y, radius};

    // TODO: This is terrible.
    tile_sprite.SetTileHexSprite(TileHexSprite{position.x, position.y, radius, TileHexSprite::RIM_COLOR, TileHexSprite::MIDDLE_COLOR, TileHexSprite::REVEALED_INTERNAL_COLOR});
    return tile_sprite;
}

TileSprite Hexasweeper::Graphics::CreateBombTile(Vector2 position, u32 radius)
{
    std::unique_ptr<ImageSprite> bomb_sprite = std::make_unique<ImageSprite>(bomb_png, Vector2{0.1, 0.1});
    bomb_sprite->SetCenter({position.x, position.y});

    TileSprite tile_sprite = TileSprite{position.x, position.y, radius, std::move(bomb_sprite)};

    // TODO: This is terrible.
    tile_sprite.SetTileHexSprite(TileHexSprite{position.x, position.y, radius, TileHexSprite::RIM_COLOR, TileHexSprite::MIDDLE_COLOR, TileHexSprite::REVEALED_INTERNAL_COLOR});
    return tile_sprite;
}

TileSprite Hexasweeper::Graphics::CreateFlagTile(Vector2 position, u32 radius)
{
    std::unique_ptr<ImageSprite> flag_sprite = std::make_unique<ImageSprite>(flag_png, Vector2{0.1, 0.1});
    flag_sprite->SetCenter(position);

    return TileSprite{position.x, position.y, radius, std::move(flag_sprite)};

}

TileSprite Hexasweeper::Graphics::CreateNearbyTile(std::shared_ptr<TTFFont> font, u8 num_nearby, Vector2 position, u32 radius)
{
    u32 color = UINT32_MAX;
    switch (num_nearby)
    {
    case 1:
        color = RGBA(0, 0, 255, 255);
        break;
    case 2:
        color = RGBA(0, 255, 0, 255);
        break;
    // TODO: Fill it in, I don't remember.
    default:
        color = RGBA(255, 0, 0, 255);
    }

    std::string nearby_string = std::to_string(num_nearby);

    std::unique_ptr<TextSprite> number_sprite = std::make_unique<TextSprite>(Vector2{position.x, position.y}, font, nearby_string, 35, color);
    number_sprite->SetCenter({position.x, position.y});

    TileSprite tile_sprite = TileSprite{position.x, position.y, radius, std::move(number_sprite)};

    // TODO: This is terrible.
    tile_sprite.SetTileHexSprite(TileHexSprite{position.x, position.y, radius, TileHexSprite::RIM_COLOR, TileHexSprite::MIDDLE_COLOR, TileHexSprite::REVEALED_INTERNAL_COLOR});
    return tile_sprite;
}
