#include "ZoneDisplayZone.h"

ZoneDisplayZone::ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
}

ZoneDisplayZone::~ZoneDisplayZone()
{
    //dtor
}

void ZoneDisplayZone::render(SDL_Surface* screen, DynamicWorld /** @todo const*/& world) const
{
    SDL_Rect displayPos = m_displayPos;
    SDL_Rect tileSetSize;
    Uint16 maxHeight = 0;

    std::vector<std::vector<std::string> > zoneSet = world.getZoneSet();

    for(std::vector<std::vector<std::string> >::iterator zYit = zoneSet.begin(); zoneSet.end() != zYit; ++zYit)
    {
        for (std::vector<std::string>::iterator zXit = zYit->begin(); zYit->end() != zXit; ++zXit)
        {
            TileDisplayZone tileDisplayZone(displayPos.x, displayPos.y);
            tileSetSize = tileDisplayZone.render(screen, world.getZone(*zXit));

            if (world.getPartyZone() == *zXit)
            {
                /** @todo Temporary */
                tileDisplayZone.render(screen, world.getPartyTile(), TILE_NONE);
            }

            displayPos.x += tileSetSize.w;
            (tileSetSize.h <= maxHeight) || (maxHeight = tileSetSize.h);
        }
        displayPos.x = m_displayPos.x;
        displayPos.y += maxHeight;
        maxHeight = 0;
    }


}
