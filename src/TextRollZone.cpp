#include "TextRollZone.h"

TextRollZone::TextRollZone(Sint16 textZoneLeft, Sint16 textZoneTop, TTF_Font* font)
{
    m_color = {255, 255, 255};
    m_font = font;
    m_textPos = {textZoneLeft, textZoneTop};
}

TextRollZone::~TextRollZone()
{
    //dtor
}

void TextRollZone::push(std::string text)
{
    m_textRoll.push_back(text);
    while (m_textRoll.size() > 5)
    {
        m_textRoll.erase(m_textRoll.begin());
    }
}

void TextRollZone::render(SDL_Surface* screen)
{
    SDL_Rect textPos = m_textPos;

    for(std::vector<std::string>::iterator it = m_textRoll.begin(); m_textRoll.end() != it; ++it)
    {
        m_textZone = TTF_RenderText_Solid(m_font, it->c_str(), m_color);
        SDL_BlitSurface(m_textZone, 0, screen, &textPos);
        SDL_FreeSurface(m_textZone);
        textPos.y += 25;
    }
}
