#ifndef TILEDISPLAYZONE_H
#define TILEDISPLAYZONE_H

#include <SDL/SDL.h>
#include <SDL/SDL_Image.h>

#include "common.h"
#include "DynamicWorld.h"

class TileDisplayZone
{
public:
    TileDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop);
    virtual ~TileDisplayZone();

    void render(SDL_Surface* screen, DynamicWorld const& world) const;
protected:
private:
    SDL_Rect m_displayPos;
    SDL_Rect m_tileMask;
    SDL_Surface **m_tiles;

    void m_computeTileMask();
};

#endif // TILEDISPLAYZONE_H
