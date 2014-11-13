#ifndef ZONEDISPLAYZONE_H
#define ZONEDISPLAYZONE_H

#include <vector>

#include <SDL/SDL.h>

#include "common.h"
#include "DynamicWorld.h"
#include "TileDisplayZone.h"

class ZoneDisplayZone
{
public:
    ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop);
    virtual ~ZoneDisplayZone();

    typedef std::vector<std::string> ZoneSetLine;
    typedef std::vector<ZoneDisplayZone::ZoneSetLine> ZoneSet;

    void render(SDL_Surface* screen, DynamicWorld  const& world) const;
protected:
private:
    SDL_Rect m_displayPos;
};

#endif // ZONEDISPLAYZONE_H
