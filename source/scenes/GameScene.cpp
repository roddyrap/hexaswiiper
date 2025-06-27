#include "GameScene.h"

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <wiiuse/wiiuse.h>

#include "hexasweeper/Game.h"
#include "sprites/RectSprite.h"
#include "WiimoteCursor.h"
#include "graphics/sprites/TextSprite.h"
#include "graphics/sprites/AutofitTextSprite.h"
#include "graphics/text/Font.h"
#include "graphics/ui/HoverButton.h"
#include "graphics/ui/ButtonFactory.h"
#include "common/Crash.h"

#include "sprites/ImageSprite.h"

#include "Player1_png.h"
#include "WiiLogo_png.h"
#include "Logo1_png.h"

#include "Roboto-Regular_ttf.h"
#include "Comfortaa-Regular_ttf.h"

#include <format>

constexpr uint32_t ACTUAL_WHITE = RGBA(255, 255, 255, 255);
constexpr uint32_t ACTUAL_BLACK = RGBA(0, 0, 0, 255);

using namespace Graphics;

std::string FormatDuration(uint64_t duration_seconds)
{
    return std::format(
        "{:02}:{:02}:{:02}",
        duration_seconds / 3600,
        (duration_seconds % 3600) / 60,
        duration_seconds % 60
    );
}

void GameScene::InitializeGame(std::shared_ptr<Font> title_font, const RectangleBounds& game_region)
{
    m_hexasweeper_game = std::make_unique<Hexasweeper::Game>(
        title_font,
        Vector2{},
        m_difficulty.board_size.y,
        m_difficulty.board_size.x,
        m_difficulty.num_bombs
    );

    m_hexasweeper_game->SetTopLeft(game_region.GetTopLeft());

    // TODO: The clipping isn't perfect, the region border is a rounded rectangle which means that
    //       the corners are incorrect (Not clipped). This is known. My idea for solving it is by
    //       rendering the inverse of the rounded rectangle after the tilemap, which would cover
    //       the edges. Will also need to treat remote presses on the edges.
    m_hexasweeper_game->SetClipRect(game_region);
}

GameScene::GameScene(Hexasweeper::Difficulty difficulty) : m_difficulty{difficulty} {}
GameScene::GameScene() : m_difficulty{Hexasweeper::TEST_DIFFICULTY} {}

void GameScene::InitializeScene()
{
    std::shared_ptr<Graphics::Font> comfortaa_font = std::make_shared<Graphics::Font>(Comfortaa_Regular_ttf, Comfortaa_Regular_ttf_size, this->GetFTLibrary());
    std::shared_ptr<Graphics::Font> roboto_font = std::make_shared<Graphics::Font>(Roboto_Regular_ttf, Roboto_Regular_ttf_size, this->GetFTLibrary());

    this->SetCursor(std::make_unique<WiimoteCursor>(WPAD_CHAN_0));

    // Initialize screen regions.
    RectangleBounds game_region = RectangleBounds{{5, 60}, {500, 415}};
    RectangleBounds settings_region = RectangleBounds{{510, 60}, {125, 80}};
    RectangleBounds info_region = RectangleBounds{{510, 145}, {125, 330}};

    this->AddSprite(std::make_unique<RoundedRectangleSprite>(
        game_region.GetTopLeft(),
        game_region.GetSize(),
        ACTUAL_BLACK,
        5,
        false
    ));
    this->AddSprite(std::make_unique<RoundedRectangleSprite>(
        settings_region.GetTopLeft(),
        settings_region.GetSize(),
        ACTUAL_BLACK,
        5,
        false
    ));
    this->AddSprite(std::make_unique<RoundedRectangleSprite>(
        info_region.GetTopLeft(),
        info_region.GetSize(),
        ACTUAL_BLACK,
        5,
        false
    ));

    // Initialize UI.
    std::unique_ptr<ImageSprite> logo_sprite = std::make_unique<ImageSprite>(Logo1_png, Vector2{0.1f, 0.1f});
    std::unique_ptr<TextSprite> logo_text = std::make_unique<TextSprite>(comfortaa_font, "Hexaswiiper");
    logo_sprite->SetPosition({5, 2});
    logo_text->SetPosition({logo_sprite->GetBounds().GetRight() + 8, 13});

    this->AddSprite(std::move(logo_sprite));
    this->AddSprite(std::move(logo_text));

    // Initialize game.
    this->InitializeGame(comfortaa_font, game_region);

    // Initialize info sprites.
    std::string difficulty_string = std::format("Difficulty: {}", m_difficulty.name);
    std::unique_ptr<AutofitTextSprite> settings_text = std::make_unique<AutofitTextSprite>(
        RectangleBounds{settings_region.GetTopLeft() + Vector2{2, 10}, Vector2{settings_region.GetSize().x - 4, 20}},
        comfortaa_font,
        difficulty_string,
        UINT32_MAX
    );

    std::unique_ptr<AutofitTextSprite> flags_left_text = std::make_unique<AutofitTextSprite>(
        RectangleBounds{info_region.GetTopLeft() + Vector2{2, 10}, Vector2{info_region.GetSize().x - 4, 20}},
        roboto_font,
        "",
        UINT32_MAX,
        Vector2U32{1, 15}
    );
    m_flags_left_text = flags_left_text.get();

    std::unique_ptr<AutofitTextSprite> time_text = std::make_unique<AutofitTextSprite>(
        RectangleBounds{info_region.GetTopLeft() + Vector2{2, 30}, Vector2{info_region.GetSize().x - 4, 20}},
        roboto_font,
        "",
        UINT32_MAX,
        Vector2U32{1, 15}
    );
    m_time_text = time_text.get();

    this->AddSprite(std::move(settings_text));
    this->AddSprite(std::move(flags_left_text));
    this->AddSprite(std::move(time_text));

    // Interactive UI.

    this->AddButton(CreateRoundedRectangleTextButton([this, game_region, comfortaa_font](){
            this->InitializeGame(comfortaa_font, game_region);
        },
        {info_region.GetBottomLeft() + Vector2{12.5f, -45}, {100.0, 30.0}},
        5,
        roboto_font,
        "Restart",
        20
    ));

    this->AddButton(CreateRoundedRectangleTextButton([this, game_region](){
            this->m_hexasweeper_game->SetTopLeft(game_region.GetTopLeft());
        },
        {info_region.GetBottomLeft() + Vector2{12.5f, -85}, {100.0, 30.0}},
        5,
        roboto_font,
        "Center Camera",
        13
    ));
}

void GameScene::UpdateScene()
{
    u32 pressedButtons = this->GetCursor()->GetPressedButtons();
    u32 heldButtons = this->GetCursor()->GetHeldButtons();

    // If [HOME] was pressed on the first Wiimote, break out of the loop
    if (pressedButtons & WPAD_BUTTON_HOME)
    {
        CRASH(0);
    }

    if (m_hexasweeper_game->GetClipRect().has_value() && m_hexasweeper_game->GetClipRect()->ContainsPoint(this->GetCursor()->GetPosition()))
    {
        if (pressedButtons & WPAD_BUTTON_A)
        {
            m_hexasweeper_game->RevealTile(this->GetCursor()->GetPosition());
        }
        else if (pressedButtons & WPAD_BUTTON_B)
        {
            m_hexasweeper_game->FlagTile(this->GetCursor()->GetPosition());
        }
    }

    Vector2 movement{0, 0};
    if (heldButtons & WPAD_BUTTON_UP) movement.y += 1.0;
    if (heldButtons & WPAD_BUTTON_DOWN) movement.y -= 1.0;
    if (heldButtons & WPAD_BUTTON_LEFT) movement.x += 1.0;
    if (heldButtons & WPAD_BUTTON_RIGHT) movement.x -= 1.0;

    m_hexasweeper_game->Move(movement * 5);

    // Draw game.
    m_hexasweeper_game->Render();

    std::string flags_left_string{};
    flags_left_string += std::format("Flags Left: {}/{}", m_hexasweeper_game->GetFlagsLeft(), m_hexasweeper_game->GetNumBombs());
    m_flags_left_text->SetText(flags_left_string);

    std::string time_passed_string{};
    if (m_hexasweeper_game->GetStartTime() == 0)
    {
        time_passed_string += std::string{"Not started yet"};
    }
    else
    {
        time_passed_string += std::string{"Time: "} + FormatDuration(time(nullptr) - m_hexasweeper_game->GetStartTime());
    }
    m_time_text->SetText(time_passed_string);
}
