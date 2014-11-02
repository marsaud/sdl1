#ifndef SCREENZONE_H
#define SCREENZONE_H

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class ScreenZone
{
public:
    ScreenZone(Sint16 const textZoneLeft, Sint16 const textZoneTop, TTF_Font* const font);
    virtual ~ScreenZone();

    void render(SDL_Surface* screen, std::string const& display);
protected:
private:
    SDL_Rect m_textPos;
    SDL_Color m_color;
    TTF_Font* m_font;
};

#endif // SCREENZONE_H
