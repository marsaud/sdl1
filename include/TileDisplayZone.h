#ifndef TILEDISPLAYZONE_H
#define TILEDISPLAYZONE_H

#include <SDL/SDL.h>
#include "common.h"
#include "DynamicWorld.h"

#include <SDL/SDL_Image.h>

class TileDisplayZone
{
    public:
        TileDisplayZone(Sint16 displayZoneLeft, Sint16 displayZoneTop);
        virtual ~TileDisplayZone();
        void render(DynamicWorld const& world, SDL_Surface* screen) const;
    protected:
    private:
        SDL_Rect m_displayPos;
        SDL_Surface **m_tiles;
};

#endif // TILEDISPLAYZONE_H
