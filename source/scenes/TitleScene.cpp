#include "TitleScene.h"

#include <vector>

#include <wiiuse/wpad.h>

#include "GameScene.h"
#include "WiimoteCursor.h"
#include "graphics/sprites/ImageSprite.h"
#include "graphics/sprites/TriangleSprite.h"
#include "graphics/ui/ButtonFactory.h"
#include "graphics/text/Font.h"
#include "hexasweeper/Difficulty.h"

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
        [this](){
            GameScene game{Hexasweeper::DIFFICULTIES[this->m_difficultyIndex]};
            game.SceneLoop();
        },
        Vector2{275, 300},
        50,
        comfortaa_font,
        "Play!",
        30
    ));

    // Difficulty selection

    this->AddSprite(std::make_unique<Graphics::TextSprite>(
        Vector2{120, 220},
        comfortaa_font,
        "Difficulty:",
        30,
        UINT32_MAX
    ));

    this->AddButton(
        std::make_unique<Graphics::HoverButton>(
            [this](){ this->ChangeDifficulty(-1); },
            std::make_unique<Graphics::TriangleSprite>(
                Vector2{300, 235},
                30,
                UINT32_MAX, 
                180,
                true
            )
        )
    );

    auto difficulty_text{std::make_unique<Graphics::TextSprite>(
        Vector2{320, 222},
        comfortaa_font,
        Hexasweeper::DIFFICULTIES[m_difficultyIndex].name,
        30,
        UINT32_MAX
    )};
    m_difficultyText = difficulty_text.get();
    this->AddSprite(std::move(difficulty_text));

    this->AddButton(
        std::make_unique<Graphics::HoverButton>(
            [this](){ this->ChangeDifficulty(1); },
            std::make_unique<Graphics::TriangleSprite>(
                Vector2{540, 235},
                30,
                UINT32_MAX, 
                0,
                true
            )
        )
    );
}

void TitleScene::ChangeDifficulty(int difference)
{
    // Overflows are fine because size_t is unsigned.
    m_difficultyIndex = (m_difficultyIndex + difference) % Hexasweeper::DIFFICULTIES.size();
    m_difficultyText->SetText(Hexasweeper::DIFFICULTIES[m_difficultyIndex].name);
}

void TitleScene::UpdateScene() {}