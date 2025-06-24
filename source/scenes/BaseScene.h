#ifndef SCENES_BASE_SCENE_H
#define SCENES_BASE_SCENE_H

#include <grrlib.h>

#include "graphics/ui/HoverButton.h"
#include "graphics/Sprite.h"
#include "WiimoteCursor.h"

class BaseScene
{
public:
    static constexpr uint32_t HEXASWEEPER_GRAY = RGBA(87, 87, 87, 255);

public:
    BaseScene();
    virtual ~BaseScene() = default;

public:
    void SceneLoop();

    void SetBackgroundColor(uint32_t color);
    uint32_t GetBackgroundColor();

    void SetCursor(std::unique_ptr<WiimoteCursor> cursor_sprite);
    WiimoteCursor *GetCursor();

    void AddSprite(std::unique_ptr<Graphics::Sprite>&& sprite);
    void AddButton(std::unique_ptr<Graphics::HoverButton>&& button);

protected:
    virtual void InitializeScene() = 0;
    virtual void UpdateScene() = 0;

    std::shared_ptr<FT_LibraryRec_> GetFTLibrary();

private:
    uint32_t m_background_color;
    std::shared_ptr<FT_LibraryRec_> m_ft_library;

    std::vector<std::unique_ptr<Graphics::Sprite>> m_sprites;
    std::vector<std::unique_ptr<Graphics::HoverButton>> m_buttons;

    std::unique_ptr<WiimoteCursor> m_cursor{nullptr};
};

#endif // SCENES_BASE_SCENE_H