#include "BaseScene.h"

#include <wiiuse/wpad.h>

BaseScene::BaseScene() : m_background_color{HEXASWEEPER_GRAY}, m_ft_library{Graphics::create_ft_library()} {}

void BaseScene::SceneLoop()
{
    GRRLIB_SetBackgroundColour(R(m_background_color), G(m_background_color), B(m_background_color), A(m_background_color));

    this->InitializeScene();

    while (true)
    {
        WPAD_ScanPads();
        this->UpdateScene();

        for (auto& sprite : m_sprites)
        {
            sprite->Render();
        }

        for (auto& button : m_buttons)
        {
            button->Render();
            if (m_cursor != nullptr)
            {
                button->ReactToMouse(
                    m_cursor->GetPosition(),
                    m_cursor->GetPressedButtons() & WPAD_BUTTON_A
                );
            }
        }

        if (m_cursor != nullptr)
        {
            m_cursor->Render();
        }

        VIDEO_WaitVSync();
        GRRLIB_Render();
    }
}

void BaseScene::SetBackgroundColor(uint32_t color)
{
    m_background_color = color;
}

uint32_t BaseScene::GetBackgroundColor()
{
    return m_background_color;
}

void BaseScene::SetCursor(std::unique_ptr<WiimoteCursor> cursor_sprite)
{
    m_cursor = std::move(cursor_sprite);
}

WiimoteCursor *BaseScene::GetCursor()
{
    return m_cursor.get();
}

void BaseScene::AddSprite(std::unique_ptr<Graphics::Sprite>&& sprite)
{
    m_sprites.push_back(std::move(sprite));
}

void BaseScene::AddButton(std::unique_ptr<Graphics::HoverButton>&& button)
{
    m_buttons.push_back(std::move(button));
}

std::shared_ptr<FT_LibraryRec_> BaseScene::GetFTLibrary()
{
    return m_ft_library;
}