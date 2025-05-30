#ifndef GRPAHICS_TEXT_FONT_H
#define GRPAHICS_TEXT_FONT_H

#include <freetype/freetype.h>

#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ft.h>

#include <grrlib.h>

#include <memory>
#include <string>

#include "common/Vector2.h"

namespace Graphics
{
    struct HBBufferDestroyer
    {
        void operator()(hb_buffer_t *p);
    };

    using owned_hb_buffer_t = std::unique_ptr<hb_buffer_t, HBBufferDestroyer>;

    std::shared_ptr<FT_LibraryRec_> create_ft_library();

    class Font
    {
    public:
        using text_size_t = uint16_t;
        static constexpr uint16_t DEFAULT_FONT_SIZE = 32;

    public:
        Font(const uint8_t* font_data, size_t font_buffer_size, std::shared_ptr<FT_LibraryRec_> ft_library);
        Font(const uint8_t* font_data, size_t font_buffer_size);
        ~Font();

        Vector2Int MeasureText(const std::string& text, text_size_t text_size);

        // NOTE: The caller is responsible for managing the texture as a resource.
        GRRLIB_texImg *Rasterize(const std::string& text, text_size_t text_size);

    private:
        owned_hb_buffer_t ShapeText(const std::string& text, text_size_t text_size);
        Vector2Int MeasureText(hb_buffer_t *hb_buffer);

        void SetTextSize(text_size_t text_size);

    private:
        // TODO: Not necessarily required.
        std::vector<char> m_raw_font_data;

        std::shared_ptr<FT_LibraryRec_> m_ft_library;
        FT_Face m_ft_face;

        std::unordered_map<text_size_t, FT_Size> m_size_map;

        hb_font_t* m_hb_font;
    };
}

#endif // GRPAHICS_TEXT_FONT_H