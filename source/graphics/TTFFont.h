#ifndef GRAPHICS_TTFFONT_H
#define GRAPHICS_TTFFONT_H

#include <stdarg.h>
#include <stdint.h>
#include <grrlib.h>

#include "GraphicsUtils.h"

namespace Graphics
{
    class TTFFont
    {
    public:
        // It's really wasteful (Loading and unloading the font each call), but can be nice
        // for quick debugging.
        static void DebugPrintf(Vector2Int position, const char* fmt, ...);

    public:
        TTFFont(const uint8_t* fontData, size_t fontDataSize, int fontSize);
        TTFFont(const uint8_t* fontData, size_t fontDataSize) :
            TTFFont(fontData, fontDataSize, DEFAULT_FONT_SIZE) {}
        ~TTFFont();

        int Printf(Vector2Int position, const char* fmt, ...);
        int Printf(Vector2Int position, const char* fmt, va_list args);

        GRRLIB_ttfFont *GetFont();
    private:
        static constexpr int DEFAULT_FONT_SIZE = 32;

        int m_fontSize{};
        GRRLIB_ttfFont* m_font;
    };
}

#endif // GRAPHICS_TTFFONT_H
