#ifndef TEXTROLLZONE_H
#define TEXTROLLZONE_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <vector>
#include <string>

class TextRollZone
{
    public:
        TextRollZone(Sint16 textZoneLeft, Sint16 textZoneTop, TTF_Font* font);
        virtual ~TextRollZone();
        void push(std::string text);
        void render(SDL_Surface* screen);
    protected:
    private:
        std::vector<std::string> m_textRoll;
        SDL_Surface* m_textZone;
        SDL_Rect m_textPos;
        SDL_Color m_color;
        TTF_Font* m_font;
};

#endif // TEXTROLLZONE_H
