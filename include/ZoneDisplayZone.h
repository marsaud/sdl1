#ifndef ZONEDISPLAYZONE_H
#define ZONEDISPLAYZONE_H

#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_Image.h>

#include "common.h"
#include "DynamicWorld.h"
#include "TileDisplayZone.h"

class ZoneDisplayZone
{
public:
    ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop);
    virtual ~ZoneDisplayZone();

    void render(SDL_Surface* screen, DynamicWorld  /** @todo const*/& world) const;
protected:
private:
    SDL_Rect m_displayPos;
};

#endif // ZONEDISPLAYZONE_H
