#ifndef SCENES_GAME_SCENE_H
#define SCENES_GAME_SCENE_H

#include "BaseScene.h"
#include "hexasweeper/Game.h"
#include "graphics/sprites/TextSprite.h"

class GameScene : public BaseScene
{
public:
    void InitializeScene();
    void UpdateScene();

private:
    std::unique_ptr<Hexasweeper::Game> m_hexasweeper_game{nullptr};

    Graphics::TextSprite *m_time_text;
    Graphics::TextSprite *m_flags_left_text;
};

#endif // SCENES_GAME_SCENE_H