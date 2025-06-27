#ifndef SCENES_TITLE_SCENE_H
#define SCENES_TITLE_SCENE_H

#include "scenes/BaseScene.h"
#include "graphics/sprites/TriangleSprite.h"

class TitleScene : public BaseScene
{
public:
    void InitializeScene();
    void UpdateScene();

private:
    void ChangeDifficulty(int difference);

private:
    Graphics::TextSprite *m_difficultyText;
    size_t m_difficultyIndex{};
};

#endif // SCENES_TITLE_SCENE_H