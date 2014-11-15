#ifndef TEXTROLLZONE_H
#define TEXTROLLZONE_H

#include <vector>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../main.h"

#define TEXTROLL_BUFFER_SIZE    6
#define TEXTROLL_SPACING        0

/**
* @todo see if we can overload operator<< to ease push
*/
class TextRollZone
{
public:
    TextRollZone(Sint16 const textZoneLeft, Sint16 const textZoneTop, TTF_Font* const font);
    virtual ~TextRollZone();

    enum Mode {FORWARD, REVERSE};

    void push(std::string const& text);
    void render(SDL_Surface* screen, TextRollZone::Mode const mode = FORWARD) const;
    void clear();

    static const unsigned int BUFFER_SIZE = TEXTROLL_BUFFER_SIZE;
    static const unsigned int SPACING = TEXTROLL_SPACING;

protected:
private:
    std::vector<std::string> m_textRoll;
    SDL_Rect m_textPos;
    SDL_Color m_color;
    TTF_Font* m_font;
};

#endif // TEXTROLLZONE_H
