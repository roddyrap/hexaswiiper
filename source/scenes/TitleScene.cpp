#include "TitleScene.h"

#include <vector>

#include <wiiuse/wpad.h>

#include "GameScene.h"
#include "WiimoteCursor.h"
#include "graphics/sprites/ImageSprite.h"
#include "graphics/ui/ButtonFactory.h"
#include "graphics/text/Font.h"

#include "Comfortaa-Regular_ttf.h"
#include "Roboto-Regular_ttf.h"

#include "Logo1_png.h"

void TitleScene::InitializeScene()
{
    std::shared_ptr<Graphics::Font> comfortaa_font = std::make_shared<Graphics::Font>(Comfortaa_Regular_ttf, Comfortaa_Regular_ttf_size, this->GetFTLibrary());

    this->SetCursor(std::make_unique<WiimoteCursor>(WPAD_CHAN_0));

    std::unique_ptr<Graphics::ImageSprite> logo_sprite = std::make_unique<Graphics::ImageSprite>(Logo1_png, Vector2{0.25f, 0.25f});
    logo_sprite->SetPosition({50, 50});

    std::unique_ptr<Graphics::TextSprite> logo_text = std::make_unique<Graphics::TextSprite>(Vector2{}, comfortaa_font, "Hexaswiiper", 65, UINT32_MAX);
    Vector2 centered_position{logo_sprite->GetBounds().GetRight() + 10, logo_sprite->GetBounds().GetTop() + logo_sprite->GetBounds().GetSize().y / 2 - logo_text->GetBounds().GetSize().y / 2};
    logo_text->SetPosition(centered_position);

    this->AddSprite(std::move(logo_text));
    this->AddSprite(std::move(logo_sprite));

    this->AddButton(Graphics::CreateHexagonTextButton(
        [](){
            GameScene game{};
            game.SceneLoop();
        },
        Vector2{275, 300},
        50,
        comfortaa_font,
        "Play!",
        30
    ));
}

void TitleScene::UpdateScene() {}