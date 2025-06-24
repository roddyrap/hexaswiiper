#ifndef GRAPHICS_LAYOUT_BOX_LAYOUT_H
#define GRAPHICS_LAYOUT_BOX_LAYOUT_H

#include "graphics/sprites/RectSprite.h"
#include <vector>
#include <memory>

namespace Graphics
{
    class BoxLayout : public RectSprite
    {
    public:
        BoxLayout(RectangleBounds bounds, bool force_color) :
            RectSprite{bounds.GetTopLeft(), bounds.GetSize(), UINT32_MAX, false},
            m_force_color{force_color}
        {
            this->UpdateChildPosition();
        }

        virtual ~BoxLayout() = default;

        void SetColor(uint32_t color) override
        {
            this->RectSprite::SetColor(color);
            if (m_force_color)
            {
                for (auto& sprite: m_sprites)
                {
                    sprite->SetColor(color);
                }
            }
        }

        void SetPosition(Vector2 position) override
        {
            this->RectSprite::SetPosition(position);
            this->UpdateChildPosition();
        }

        void SetSize(Vector2 size) override
        {
            this->RectSprite::SetSize(size);
            this->UpdateChildPosition();
        }

        void Render() override
        {
            for (auto& sprite : m_sprites)
            {
                sprite->Render();
            }
        }

        void AddSprite(std::unique_ptr<RectSprite>&& new_sprite)
        {
            new_sprite->SetCenter(this->GetCenter());
            m_sprites.push_back(std::move(new_sprite));
        }

    private:
        void UpdateChildPosition()
        {
            for (auto& sprite: m_sprites)
            {
                sprite->SetCenter(this->GetCenter());
            }
        }

    private:
        std::vector<std::unique_ptr<RectSprite>> m_sprites;

        // Child options.
        bool m_force_color;
    };
}

#endif // GRAPHICS_LAYOUT_BOX_LAYOUT_H