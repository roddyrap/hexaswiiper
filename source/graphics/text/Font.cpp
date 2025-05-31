#include "Font.h"

#include "common/Crash.h"

#include <freetype/ftsizes.h>

#include <cmath>

using namespace Graphics;

constexpr int BIT6_MASK = 0b111111;

#define GET_FT_F26Dot6_WHOLE(a) ((a) >> 6)
#define GET_FT_F26Dot6_PARTIAL(a) ((a) & BIT6_MASK)

#define GET_FT_F26Dot6_FLOAT(a) (static_cast<float>(GET_FT_F26Dot6_WHOLE((a))) + (static_cast<float>(GET_FT_F26Dot6_PARTIAL((a))) / BIT6_MASK))

#define F26Dot6_WHOLE(a) ((a) << 6)

#define GET_FT_F16Dot16_WHOLE(a) ((a) >> 16)
#define GET_FT_F16Dot16_PARTIAL(a) ((a) & UINT16_MAX)


#define FT_ASSERT(ft_call)                                                                \
    do                                                                                    \
    {                                                                                     \
        auto __ft_error = (ft_call);                                                      \
        if (__ft_error != 0)                                                              \
        {                                                                                 \
            SYS_Report("FT Error: %s (0x%x)\n", FT_Error_String(__ft_error), __ft_error); \
            CRASH(1);                                                                     \
        }                                                                                 \
    } while (0)

using Vector2Pos = Vector2Base<FT_Pos>;

void Graphics::HBBufferDestroyer::operator()(hb_buffer_t *p)
{
    hb_buffer_destroy(p);
}

std::shared_ptr<FT_LibraryRec_> Graphics::create_ft_library()
{
    FT_Library ft_library{nullptr};
    FT_Init_FreeType(&ft_library);

    return std::shared_ptr<FT_LibraryRec_>{ft_library, FT_Done_FreeType};
}

Graphics::Font::Font(const uint8_t* font_data, size_t font_buffer_size, std::shared_ptr<FT_LibraryRec_> ft_library) :
    m_raw_font_data{font_data, font_data + font_buffer_size}, m_ft_library{ft_library}, m_size_map{}
{
    if (m_ft_library == nullptr)
    {
        m_ft_library = create_ft_library();
    }

    FT_ASSERT(FT_New_Memory_Face(m_ft_library.get(), font_data, font_buffer_size, 0, &m_ft_face));

    m_hb_font = hb_ft_font_create_referenced(m_ft_face);

    ASSERT_NOT_NULL(m_hb_font);
}

Graphics::Font::Font(const uint8_t* font_data, size_t font_buffer_size) :
    Font{font_data, font_buffer_size, nullptr} {}

Graphics::Font::~Font()
{
    hb_font_destroy(m_hb_font);
}

Vector2Int Graphics::Font::MeasureText(const std::string& text, text_size_t text_size)
{
    owned_hb_buffer_t hb_buffer= this->ShapeText(text, text_size);

    return this->MeasureText(hb_buffer.get());
}

// In order to consider subpixel size values, this method reads the hb/ft positions in their native
// F26Dot6 form, only converting to actual pixel integers at the end.
// This means integers aren't really integers.
Vector2Int Graphics::Font::MeasureText(hb_buffer_t *hb_buffer)
{
    unsigned int glyph_count = 0;
    hb_glyph_position_t *glyph_pos = hb_buffer_get_glyph_positions(hb_buffer, &glyph_count);
    ASSERT_NOT_NULL(glyph_pos);

    hb_glyph_info_t *glyph_info = hb_buffer_get_glyph_infos(hb_buffer, &glyph_count);
    ASSERT_NOT_NULL(glyph_info);

    Vector2Pos text_size{0, 0};
    Vector2Pos glyph_advance{0, 0};
    for (unsigned int glyph_index = 0; glyph_index < glyph_count; ++glyph_index)
    {
        // Need to load freetype glyph in order to get actual glyph sizes.
        FT_ASSERT(FT_Load_Glyph(m_ft_face, glyph_info[glyph_index].codepoint, FT_LOAD_DEFAULT));

        Vector2Pos glyph_size = Vector2Pos{
            m_ft_face->glyph->metrics.width,
            m_ft_face->glyph->metrics.height
        };

        FT_Pos x_advance = glyph_pos[glyph_index].x_advance;
        FT_Pos y_advance = glyph_pos[glyph_index].y_advance;
        FT_Pos x_offset = glyph_pos[glyph_index].x_offset;
        FT_Pos y_offset = glyph_pos[glyph_index].y_offset;

        Vector2Pos hb_glyph_offset = Vector2Pos{x_offset, y_offset};

        // Calculate the size of the previous glyphs if there's overlap and one is bigger, or the current extents. 
        text_size = Vector2Pos{
            MAX(text_size.x, glyph_advance.x + hb_glyph_offset.x + glyph_size.x),
            MAX(text_size.y, glyph_advance.y + hb_glyph_offset.y + glyph_size.y)
        };

        glyph_advance += Vector2Pos{x_advance, y_advance};
    }

    return Vector2Int{
        static_cast<int>(std::ceil(GET_FT_F26Dot6_FLOAT(text_size.x))),
        static_cast<int>(std::ceil(GET_FT_F26Dot6_FLOAT(text_size.y)))
    };
}

// NOTE: The caller is responsible for managing the texture as a resource.
// TODO: 'y', 'g' and 'p' are't rendered correctly (Missing bottom) for some reason.
GRRLIB_texImg *Graphics::Font::Rasterize(const std::string& text, text_size_t text_size)
{
    owned_hb_buffer_t hb_buffer= this->ShapeText(text, text_size);
    Vector2Int text_dimensions = this->MeasureText(hb_buffer.get());

    // Even though it's not documented FUCKING ANYWHERRE, the texture size needs to be divisible by 4.
    Vector2Int div_four_text_dimensions{text_dimensions.x + 4 - text_dimensions.x % 4, text_dimensions.y + 4 - text_dimensions.y % 4};
    GRRLIB_texImg *texture = GRRLIB_CreateEmptyTexture(div_four_text_dimensions.x, div_four_text_dimensions.y);
    ASSERT_NOT_NULL(texture);

    unsigned int glyph_count = 0;

    hb_glyph_info_t *glyph_info = hb_buffer_get_glyph_infos(hb_buffer.get(), &glyph_count);
    ASSERT_NOT_NULL(glyph_info);

    hb_glyph_position_t *glyph_pos = hb_buffer_get_glyph_positions(hb_buffer.get(), &glyph_count);
    ASSERT_NOT_NULL(glyph_pos);

    Vector2Pos text_advance{0, 0};
    for (unsigned int glyph_index = 0; glyph_index < glyph_count; ++glyph_index)
    {
        FT_Pos x_advance = glyph_pos[glyph_index].x_advance;
        FT_Pos y_advance = glyph_pos[glyph_index].y_advance;
        FT_Pos x_offset = glyph_pos[glyph_index].x_offset;
        FT_Pos y_offset = glyph_pos[glyph_index].y_offset;

        FT_ASSERT(FT_Load_Glyph(m_ft_face, glyph_info[glyph_index].codepoint, FT_LOAD_DEFAULT | FT_LOAD_RENDER));
        ASSERT_NOT_NULL(m_ft_face->glyph);

        // I think it can happen for non-graphical glyphs like space.
        if (m_ft_face->glyph->bitmap.buffer == nullptr)
        {
            text_advance = text_advance + Vector2Pos{x_advance, y_advance};
            continue;
        }

        // TODO: I need to find a more efficient way to convert the FT bmp data to grrlib texture.
        for (size_t bmp_row = 0; bmp_row < m_ft_face->glyph->bitmap.rows; ++bmp_row)
        {
            for (size_t bmp_col = 0; bmp_col < m_ft_face->glyph->bitmap.width; ++bmp_col)
            {
                // FT_RENDER_MODE_NORMAL is a one byte per pixel alpha channel mapping.
                size_t flat_index = bmp_row * m_ft_face->glyph->bitmap.width + bmp_col;
                uint8_t grayscale = m_ft_face->glyph->bitmap.buffer[flat_index];

                // Place the glyph in the correct location, provided by harfbuzz.
                size_t texture_row = static_cast<int>(std::round(GET_FT_F26Dot6_FLOAT(text_advance.y + y_offset))) - (m_ft_face->glyph->bitmap_top) + bmp_row + texture->h;
                size_t texture_col = static_cast<int>(std::round(GET_FT_F26Dot6_FLOAT(text_advance.x + x_offset))) + (m_ft_face->glyph->bitmap_left) + bmp_col;
                if (texture_row < 0 || texture_row >= texture->h || texture_col < 0 || texture_col >= texture->w)
                {
                    // TODO: Is there a way to make this a warning?
                    SYS_Report("Invalid Texture coordinates (%zu, %zu) (Size: (%zu, %zu))\n", texture_col, texture_row, texture->w, texture->h);
                    continue;
                }

                // Add the alpha value to the current one in the pixel and set color to white. 
                u32 grrlib_current = GRRLIB_GetPixelFromtexImg(texture_col, texture_row, texture);
                u32 blended_color = RGBA(255, 255, 255, MIN(255, A(grrlib_current) + grayscale));
                if (blended_color != 0)
                {
                    GRRLIB_SetPixelTotexImg(texture_col, texture_row, texture, blended_color);
                }
            }
        }

        text_advance = text_advance + Vector2Pos{x_advance, y_advance};
    }

    return texture;
}

owned_hb_buffer_t Graphics::Font::ShapeText(const std::string& text, text_size_t text_size)
{
    SetTextSize(text_size);

    owned_hb_buffer_t hb_buffer{hb_buffer_create()};
    ASSERT_NOT_NULL(hb_buffer.get());

    if (!hb_buffer_allocation_successful(hb_buffer.get()))
    {
        CRASH(1);
    }

    hb_buffer_add_utf8(hb_buffer.get(), text.c_str(), text.size(), 0, -1);

    hb_buffer_guess_segment_properties(hb_buffer.get());

    ASSERT_EQUAL(hb_shape_full(m_hb_font, hb_buffer.get(), nullptr, 0, NULL), true);

    return hb_buffer;
}

void Graphics::Font::SetTextSize(text_size_t text_size)
{
    if (text_size == 0) text_size = DEFAULT_FONT_SIZE;

    if (!m_size_map.contains(text_size))
    {
        m_size_map[text_size] = {};
        FT_ASSERT(FT_New_Size(m_ft_face, &m_size_map[text_size]));

        FT_ASSERT(FT_Activate_Size(m_size_map[text_size]));
        FT_ASSERT(FT_Set_Char_Size(m_ft_face, 0, F26Dot6_WHOLE(text_size), 0, 0));
    }
    else
    {
        FT_ASSERT(FT_Activate_Size(m_size_map[text_size]));
    }

    // Notify HarfBuzz to fetch spacing changes.
    hb_ft_font_changed(m_hb_font);
}
