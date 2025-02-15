#ifndef GRAPHICS_TTFONT_H
#define GRAPHICS_TTFONT_H

#include <stdarg.h>
#include <stdint.h>
#include <grrlib.h>

#include "GraphicsUtils.h"

namespace Graphics
{
    class TTFont
    {
    public:
        // It's really wasteful (Loading and unloading the font each call), but can be nice
        // for quick debugging.
        static void DebugPrintf(Vector2Int position, const char* fmt, ...);

    public:
        TTFont(const uint8_t* fontData, size_t fontDataSize, int fontSize);
        TTFont(const uint8_t* fontData, size_t fontDataSize) :
            TTFont(fontData, fontDataSize, DEFAULT_FONT_SIZE) {}
        ~TTFont();

        int Printf(Vector2Int position, const char* fmt, ...);
        int Printf(Vector2Int position, const char* fmt, va_list args);
    private:
        static constexpr int DEFAULT_FONT_SIZE = 32;

        int m_fontSize{};
        GRRLIB_ttfFont* m_font;
    };
}

#endif // GRAPHICS_TTFONT_H
