#include "TTFFont.h"
#include <stdio.h>

#include "Roboto-Regular_ttf.h"

namespace Graphics
{
    void TTFFont::DebugPrintf(Vector2Int position, const char* fmt, ...)
    {
        TTFFont robotoFont{Roboto_Regular_ttf, Roboto_Regular_ttf_size};

        va_list printf_args;
        va_start(printf_args, fmt);
        robotoFont.Printf(position, fmt, printf_args);
        va_end(printf_args);
    }

    TTFFont::TTFFont(const uint8_t *fontData, size_t fontDataSize, int fontSize)
    {
        m_font = GRRLIB_LoadTTF(fontData, fontDataSize);
        m_fontSize = fontSize;
    }

    TTFFont::~TTFFont()
    {
        GRRLIB_FreeTTF(m_font);
    }

    int TTFFont::Printf(Vector2Int position, const char* fmt, ...)
    {
        va_list printf_args;
        va_start(printf_args, fmt);
        int printfResult = this->Printf(position, fmt, printf_args);
        va_end(printf_args);

        return printfResult;
    }

    int TTFFont::Printf(Vector2Int position, const char* fmt, va_list args)
    {
        char* printfBuffer = nullptr;
        int printfResult = vasprintf(&printfBuffer, fmt, args);

        if (printfBuffer != nullptr)
        {
            GRRLIB_PrintfTTF(position.x, position.y, m_font, printfBuffer, m_fontSize, COLOR_WHITE);
            free(printfBuffer);
        }

        return printfResult;
    }

    GRRLIB_ttfFont *TTFFont::GetFont()
    {
        return m_font;
    }
}