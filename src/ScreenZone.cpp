#include "ScreenZone.h"

ScreenZone::ScreenZone(Sint16 textZoneLeft, Sint16 textZoneTop, TTF_Font* font)
{
    m_color = {255, 255, 255};
    m_font = font;
    m_textPos = {textZoneLeft, textZoneTop};
}

ScreenZone::~ScreenZone()
{

}

void ScreenZone::render(std::string const& display, SDL_Surface* screen)
{
    m_text = TTF_RenderText_Solid(m_font, display.c_str(), m_color);
    SDL_BlitSurface(m_text, 0, screen, &m_textPos);
    SDL_FreeSurface(m_text);
}
