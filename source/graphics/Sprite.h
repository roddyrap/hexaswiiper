#ifndef SPRITE_H
#define SPRITE_H

#include "RectangleBounds.h"

#include <vector>

namespace Graphics
{
    class Sprite
    {
    public:
        static void RenderActive();

        Sprite();
        virtual ~Sprite();

        virtual void Render() = 0;
        virtual Vector2 GetPosition() = 0;

        // If sprite should be drawn to screen.
        void SetActive();
        void SetInactive();
    private:
        static std::vector<Sprite*> sprites;

        bool m_active = true;
    };
}

#endif // SPRITE_H