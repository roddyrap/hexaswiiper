#ifndef RECT_SPRITE_H
#define RECT_SPRITE_H

#include <stdint.h>

#include "Sprite.h"

namespace Graphics
{
    class RectSprite : public Sprite
    {
    public:
        RectSprite(Vector2 position, Vector2 size, uint32_t color, bool fill) : 
            m_position{position}, m_size{size}, m_color{color}, m_fill{fill}
        {}

        virtual void Render() override;

        virtual Vector2 GetPosition() const override;
        virtual Vector2 GetCenter() const;
        virtual uint32_t GetColor() const;
        virtual Vector2 GetSize() const;
        virtual bool GetFill() const;

        virtual void SetPosition(Vector2 position);
        virtual void SetCenter(Vector2 position);
        virtual void SetColor(uint32_t color);
        virtual void SetSize(Vector2 size);

        virtual RectangleBounds GetBounds() const;
    protected:
        Vector2 m_position;
        Vector2 m_size;
        uint32_t m_color;

    private:
        bool m_fill;
    };
}

#endif // RECT_SPRITE_H