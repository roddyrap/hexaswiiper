#ifndef HEXASWEEPER_GRAPHICS_TILE_DRAWING_H
#define HEXASWEEPER_GRAPHICS_TILE_DRAWING_H

#include <grrlib.h>

#include "common/Vector2.h"
#include "hexasweeper/logic/Board.h"
#include "graphics/text/Font.h"

#include <string>
#include <map>

namespace Hexasweeper
{
    class TileRenderer
    {
    public:
        static constexpr u32 HIDDEN_INTERNAL_COLOR = RGBA(130, 130, 130, 255);
        static constexpr u32 REVEALED_INTERNAL_COLOR = RGBA(200, 200, 200, 255);

        static constexpr u32 MIDDLE_COLOR = RGBA(80, 80, 80, 255);
        static constexpr u32 RIM_COLOR = RGBA(0, 0, 0, 255);

        static constexpr u32 TILE_FONT_SIZE = 35;

        static constexpr std::array <u32, 6> NEARBY_COLORS{
            RGBA(0, 0, 255, 255),
            RGBA(0, 127, 14, 255),
            RGBA(255, 0, 0, 255),
            RGBA(0, 19, 127, 255),
            RGBA(127, 0, 0, 255),
            RGBA(0, 148, 255, 255)
        };

    public:
        TileRenderer(std::shared_ptr<::Graphics::Font> font, u32 hexagon_radius);
        virtual ~TileRenderer();

    public:
        // General function that is meant to be used outside.
        void DrawTile(Vector2 center, Hexasweeper::Logic::TileState state);

        u32 GetHexagonRadius();
    private:
        // Specific tiles draw implementation.

        void DrawHiddenTile(Vector2 center);

        void DrawRevealedTile(Vector2 center);

        void DrawBombTile(Vector2 center);

        void DrawFlagTile(Vector2 center);

        void DrawNumberTile(Vector2 center, u8 num_nearby);

        // Shared drawing functions.

        void DrawBaseHexagon(Vector2 center, bool revealed);

        // Utility functions.

        void DrawFlag(Vector2 center);
        void DrawBomb(Vector2 center);
        void DrawNumber(Vector2 center, u8 number);

    private:
        std::shared_ptr<::Graphics::Font> m_font;
        uint32_t m_hexagon_radius;

        std::map<u8, GRRLIB_texImg *> m_numberTextures;
        GRRLIB_texImg *m_flagTexture;
        GRRLIB_texImg *m_bombTexture;
    };
}

#endif // HEXASWEEPER_GRAPHICS_TILE_DRAWING_H