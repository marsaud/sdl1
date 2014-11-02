#ifndef TILEDISPLAYZONE_H
#define TILEDISPLAYZONE_H

#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_Image.h>

#include "common.h"
#include "DynamicWorld.h"

class TileDisplayZone
{
public:
    TileDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop);
    virtual ~TileDisplayZone();
    // SDL_Rect getTileMask() const;
    SDL_Rect render(SDL_Surface* screen, DynamicWorld const& world) const;
    SDL_Rect render(SDL_Surface* screen, DynamicWorld::TileSet const& tileSet) const;
    SDL_Rect render(SDL_Surface* screen, Position tilePos, Tile tile) const;
protected:
private:
    SDL_Rect m_displayPos;
    SDL_Rect m_tileMask;
    SDL_Surface **m_tiles;

    void m_computeTileMask();
};

#endif // TILEDISPLAYZONE_H
