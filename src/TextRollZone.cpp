#include "TextRollZone.h"

TextRollZone::TextRollZone(Sint16 const textZoneLeft, Sint16 const textZoneTop, TTF_Font* const font)
{
    m_color = {255, 255, 255};
    m_font = font;
    m_textPos = {textZoneLeft, textZoneTop};
}

TextRollZone::~TextRollZone()
{
    //dtor
}

void TextRollZone::push(std::string const text)
{
    m_textRoll.push_back(text);
    while (m_textRoll.size() > TextRollZone::BUFFER_SIZE)
    {
        m_textRoll.erase(m_textRoll.begin());
    }
}

void TextRollZone::render(SDL_Surface* screen, TextRollZone::Mode const reverse) const
{
    SDL_Rect textPos = m_textPos;
    SDL_Surface* textZone = NULL;
    int step = FONT_SIZE + TextRollZone::SPACING;

    if (REVERSE == reverse)
    {
        textPos.y += ((TextRollZone::BUFFER_SIZE - 1) * step);
        step = -step;
    }

    for(std::vector<std::string>::const_iterator it = m_textRoll.cbegin(); m_textRoll.cend() != it; ++it)
    {
        textZone = TTF_RenderText_Solid(m_font, it->c_str(), m_color);
        SDL_BlitSurface(textZone, 0, screen, &textPos);
        SDL_FreeSurface(textZone);
        textPos.y += step;
    }
}

void TextRollZone::clear()
{
    m_textRoll.clear();
}
