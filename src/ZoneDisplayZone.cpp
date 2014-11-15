#include "ZoneDisplayZone.h"

ZoneDisplayZone::ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
}

ZoneDisplayZone::~ZoneDisplayZone()
{
    //dtor
}

void ZoneDisplayZone::render(SDL_Surface* screen, const StaticArea* area, PartyPlayer* player) const
{
    SDL_Rect displayPos = m_displayPos;
    SDL_Rect tileSetSize;
    Uint16 maxHeight = 0;

    for(ZoneDisplayZone::ZoneSet::const_iterator zYit = area->getZoneSet().cbegin(); area->getZoneSet().cend() != zYit; ++zYit)
    {
        for (ZoneDisplayZone::ZoneSetLine::const_iterator zXit = zYit->cbegin(); zYit->cend() != zXit; ++zXit)
        {
            TileDisplayZone tileDisplayZone(displayPos.x, displayPos.y);
            tileSetSize = tileDisplayZone.render(screen, area->getZone(*zXit));

            if (player->getZoneKey() == *zXit)
            {
                /** @todo Temporary */
                tileDisplayZone.render(screen, player->getTile(), TILE_PARTY);
            }

            displayPos.x += tileSetSize.w;
            (tileSetSize.h <= maxHeight) || (maxHeight = tileSetSize.h);
        }
        displayPos.x = m_displayPos.x;
        displayPos.y += maxHeight;
        maxHeight = 0;
    }
}
