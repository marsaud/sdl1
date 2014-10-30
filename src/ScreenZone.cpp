#include "ScreenZone.h"

ScreenZone::ScreenZone(Sint16 const textZoneLeft, Sint16 const textZoneTop, TTF_Font* const font)
{
    m_color = {255, 255, 255};
    m_font = font;
    m_textPos = {textZoneLeft, textZoneTop};
}

ScreenZone::~ScreenZone()
{

}

void ScreenZone::render(SDL_Surface* screen, std::string const& display)
{
    m_text = TTF_RenderText_Solid(m_font, display.c_str(), m_color);
    SDL_BlitSurface(m_text, 0, screen, &m_textPos);
    SDL_FreeSurface(m_text);
}
