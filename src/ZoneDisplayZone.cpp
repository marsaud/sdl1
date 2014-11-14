#include "ZoneDisplayZone.h"

ZoneDisplayZone::ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
}

ZoneDisplayZone::~ZoneDisplayZone()
{
    //dtor
}

void ZoneDisplayZone::render(SDL_Surface* screen, DynamicWorld const& world) const
{
    SDL_Rect displayPos = m_displayPos;
    SDL_Rect tileSetSize;
    Uint16 maxHeight = 0;

    ZoneDisplayZone::ZoneSet zoneSet = world.getZoneSet(); /** @todo why not const ? */

    for(ZoneDisplayZone::ZoneSet::iterator zYit = zoneSet.begin(); zoneSet.end() != zYit; ++zYit)
    {
        for (ZoneDisplayZone::ZoneSetLine::iterator zXit = zYit->begin(); zYit->end() != zXit; ++zXit)
        {
            TileDisplayZone tileDisplayZone(displayPos.x, displayPos.y);
            tileSetSize = tileDisplayZone.render(screen, world.getZone(*zXit));

            if (world.getPartyZone() == *zXit)
            {
                /** @todo Temporary */
                tileDisplayZone.render(screen, world.getPartyTile(), TILE_PARTY);
            }

            displayPos.x += tileSetSize.w;
            (tileSetSize.h <= maxHeight) || (maxHeight = tileSetSize.h);
        }
        displayPos.x = m_displayPos.x;
        displayPos.y += maxHeight;
        maxHeight = 0;
    }
}
