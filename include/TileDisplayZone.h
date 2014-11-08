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

    static void init();
    static void free();

    SDL_Rect render(SDL_Surface* screen, DynamicWorld const& world) const;
    SDL_Rect render(SDL_Surface* screen, DynamicWorld::TileSet const& tileSet) const;
    SDL_Rect render(SDL_Surface* screen, Position tilePos, Tile tile) const;
protected:
private:
    static SDL_Surface **ms_tiles;
    static SDL_Rect ms_tileMask;

    static void ms_loadTiles();
    static void ms_computeTileMask();

    SDL_Rect m_displayPos;
    SDL_Rect m_tileMask;
    SDL_Surface **m_tiles;

    void m_computeTileMask();
};

#endif // TILEDISPLAYZONE_H
