#ifndef GRAPHICS_SCOPED_TTF_FONT_H
#define GRAPHICS_SCOPED_TTF_FONT_H

#include <grrlib.h>
#include <memory>

template <class... Args>
std::shared_ptr<GRRLIB_ttfFont> load_ttf_font(Args&&... args) {
    return std::shared_ptr<GRRLIB_ttfFont>(GRRLIB_LoadTTF(std::forward<Args>(args)...), GRRLIB_FreeTTF);
}

#endif // GRAPHICS_SCOPED_TTF_FONT_H