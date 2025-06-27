#include "TileRenderer.h"

#include "graphics/Shapes.h"
#include "flag_png.h"
#include "bomb_png.h"

#include <format>

using namespace Hexasweeper;

TileRenderer::TileRenderer(std::shared_ptr<::Graphics::Font> font, u32 hexagon_radius) :
    m_font{font},
    m_hexagon_radius{hexagon_radius}
{
    m_flagTexture = GRRLIB_LoadTexture(flag_png);
    m_bombTexture = GRRLIB_LoadTexture(bomb_png);
}

TileRenderer::~TileRenderer()
{
    GRRLIB_FreeTexture(m_flagTexture);
    GRRLIB_FreeTexture(m_bombTexture);

    for (auto& texture : m_numberTextures)
    {
        GRRLIB_FreeTexture(texture.second);
    }
}

void TileRenderer::DrawTile(Vector2 center, Hexasweeper::Logic::TileState state)
{
    if (state.is_flagged)
    {
        DrawFlagTile(center);
    }
    else if (!state.is_revealed)
    {
        DrawHiddenTile(center);
    }
    else if (state.is_bomb)
    {
        DrawBombTile(center);
    }
    else if (state.bombs_nearby == 0)
    {
        DrawRevealedTile(center);
    }
    else
    {
        DrawNumberTile(center, state.bombs_nearby);
    }
}

u32 TileRenderer::GetHexagonRadius()
{
    return m_hexagon_radius;
}

void TileRenderer::DrawHiddenTile(Vector2 center)
{
    DrawBaseHexagon(center, false);
}

void TileRenderer::DrawRevealedTile(Vector2 center)
{
    DrawBaseHexagon(center, true);
}

void TileRenderer::DrawBombTile(Vector2 center)
{
    DrawBaseHexagon(center, true);
    DrawBomb(center);
}

void TileRenderer::DrawFlagTile(Vector2 center)
{
    DrawBaseHexagon(center, false);
    DrawFlag(center);
}

void TileRenderer::DrawNumberTile(Vector2 center, u8 num_nearby)
{
    DrawBaseHexagon(center, true);
    DrawNumber(center, num_nearby);
}

void TileRenderer::DrawBaseHexagon(Vector2 center, bool revealed)
{
    uint32_t inner_color = revealed ? REVEALED_INTERNAL_COLOR : HIDDEN_INTERNAL_COLOR;

    ::Graphics::Draw_PointyHexagon(center.x, center.y, m_hexagon_radius, RIM_COLOR, true);
    ::Graphics::Draw_PointyHexagon(center.x, center.y, m_hexagon_radius * 0.92, MIDDLE_COLOR, true);
    ::Graphics::Draw_PointyHexagon(center.x, center.y, m_hexagon_radius * 0.84, inner_color, true);
}

void TileRenderer::DrawFlag(Vector2 center)
{
    float scale = 0.1f;
    Vector2 topleft{center.x - (m_flagTexture->w * scale) / 2.0f, center.y - (m_flagTexture->h * scale) / 2.0f};
    GRRLIB_DrawImg(topleft.x, topleft.y, m_flagTexture, 0, scale, scale, UINT32_MAX);
}

void TileRenderer::DrawBomb(Vector2 center)
{
    float scale = 0.1f;
    Vector2 topleft{center.x - (m_bombTexture->w * scale) / 2, center.y - (m_bombTexture->h * scale) / 2.0f};
    GRRLIB_DrawImg(topleft.x, topleft.y, m_bombTexture, 0, scale, scale, UINT32_MAX);
}

void TileRenderer::DrawNumber(Vector2 center, u8 number)
{
    GRRLIB_texImg *number_texture{nullptr};
    if (m_numberTextures.contains(number))
    {
        number_texture = m_numberTextures[number];
    }
    else
    {
        number_texture = m_font->Rasterize(std::format("{}", number), TILE_FONT_SIZE);
        m_numberTextures[number] = number_texture;
    }

    uint32_t text_color = UINT32_MAX;
    if (number > 0 && number - 1U < NEARBY_COLORS.size())
    {
        text_color = NEARBY_COLORS[number - 1];
    }

    Vector2 topleft{center.x - number_texture->w / 2, center.y - number_texture->h / 2};
    GRRLIB_DrawImg(topleft.x, topleft.y, number_texture, 0, 1.0f, 1.0f, text_color);
}
