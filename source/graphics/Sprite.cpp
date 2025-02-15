#include "Sprite.h"

#include <algorithm>

namespace Graphics
{
    std::vector<Sprite*> Sprite::sprites{};

    Sprite::Sprite()
    {
        sprites.push_back(this);
    }

    Sprite::~Sprite()
    {
        const auto spriteIter = std::find(sprites.begin(), sprites.end(), this);
        if (spriteIter != sprites.end())
        {
            sprites.erase(spriteIter);
        }
    }

    void Sprite::RenderActive()
    {
        for (const auto& currentSprite: sprites)
        {
            if (currentSprite->m_active)
            {
                currentSprite->Render();
            }
        }
    }


    void Sprite::SetActive()
    {
        m_active = true;
    }

    void Sprite::SetInactive()
    {
        m_active = false;
    }
}