#ifndef SCREENZONE_H
#define SCREENZONE_H

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class ScreenZone
{
    public:
        ScreenZone(Sint16 textZoneLeft, Sint16 textZoneTop, TTF_Font* font);
        virtual ~ScreenZone();
        void render(std::string const& display, SDL_Surface* screen);
    protected:
    private:
        SDL_Surface* m_text;
        SDL_Rect m_textPos;
        SDL_Color m_color;
        TTF_Font* m_font;
};

#endif // SCREENZONE_H
