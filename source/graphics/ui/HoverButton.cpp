#include "HoverButton.h"

using namespace Graphics;

HoverButton::HoverButton(callback_t callback, std::unique_ptr<RectSprite>&& rect_sprite) :
    RectSprite{rect_sprite->GetPosition(), rect_sprite->GetSize(), rect_sprite->GetColor(), false},
    m_callback{callback},
    m_sprite{rect_sprite.release()}
{
    m_inactive_color = this->GetColor();
    this->SetCurrentColor(m_inactive_color);
}

void HoverButton::Render()
{
    m_sprite->Render();
}

Vector2 HoverButton::GetPosition() const
{
    return m_sprite->GetPosition();
}

void HoverButton::SetPosition(Vector2 position)
{
    m_sprite->SetPosition(position);
}

void HoverButton::SetColor(uint32_t color)
{
    this->SetCurrentColor(color);
    m_inactive_color = color;
}

void HoverButton::SetCurrentColor(uint32_t color)
{
    m_sprite->SetColor(color);
}

HoverButton::callback_t HoverButton::GetCallback() const
{
    return m_callback;
}

void HoverButton::ReactToCursor(Vector2 cursor_position, bool is_pressed)
{
    uint64_t current_time = SYS_Time();

    bool is_hovering = m_sprite->IsPositionHovering(cursor_position);
    if (m_is_hovering != is_hovering)
    {
        m_hover_changed_time = current_time;
    }

    m_is_hovering = is_hovering;

    // Blend colors.
    uint32_t r = R(m_inactive_color);
    uint32_t g = G(m_inactive_color);
    uint32_t b = B(m_inactive_color);
    uint32_t a = A(m_inactive_color);

    float blend_fraction = static_cast<float>(current_time - m_hover_changed_time) / COLOR_LERP_TICKS;
    blend_fraction = clamp(0.0f, 1.0f, blend_fraction);
    if (!m_is_hovering)
    {
        blend_fraction = 1.0f - blend_fraction;
    }

    uint32_t new_color = RGBA(
        linear_interpolate(r, R(HOVER_COLOR), blend_fraction),
        linear_interpolate(g, G(HOVER_COLOR), blend_fraction),
        linear_interpolate(b, B(HOVER_COLOR), blend_fraction),
        linear_interpolate(a, A(HOVER_COLOR), blend_fraction)
    );
    this->SetCurrentColor(new_color);

    // Check for press.
    if (is_pressed && m_is_hovering)
    {
        this->Call();
    }
}
