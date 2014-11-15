#include "ZoneDisplayZone.h"

ZoneDisplayZone::ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
}

ZoneDisplayZone::~ZoneDisplayZone()
{
    //dtor
}

void ZoneDisplayZone::render(SDL_Surface* screen, const StaticArea* area, PartyPlayer* player, SDL_Rect const offset) const
{
    /*std::unordered_map<int, PartyPlayer*> players;

    players[player->getKey()] = player;
    render(screen, area, players, offset);*/
}

void ZoneDisplayZone::render(SDL_Surface* screen, const StaticArea* area, std::unordered_map<int, PartyPlayer*> players, SDL_Rect const offset) const
{
    SDL_Rect refDisplayPos = m_displayPos;
    refDisplayPos.x += offset.x;
    refDisplayPos.y += offset.y;
    SDL_Rect displayPos = refDisplayPos;
    SDL_Rect tileSetSize;
    Uint16 maxHeight = 0;

    for (ZoneDisplayZone::ZoneSet::const_iterator zYit = area->getZoneSet().cbegin(); area->getZoneSet().cend() != zYit; ++zYit)
    {
        for (ZoneDisplayZone::ZoneSetLine::const_iterator zXit = zYit->cbegin(); zYit->cend() != zXit; ++zXit)
        {
            TileDisplayZone tileDisplayZone(displayPos.x, displayPos.y);
            tileSetSize = tileDisplayZone.render(screen, area->getZone(*zXit));

            for (std::unordered_map<int, PartyPlayer*>::const_iterator itr = players.cbegin(); players.cend() != itr; ++itr)
            {
                if ((itr->second->getArea() == area->getKey()) && (itr->second->getZoneKey() == *zXit))
                {
                    /** @todo Temporary */
                    tileDisplayZone.render(screen, itr->second->getTile(), TILE_PARTY);
                }
            }

            displayPos.x += tileSetSize.w;
            (tileSetSize.h <= maxHeight) || (maxHeight = tileSetSize.h);
        }
        displayPos.x = refDisplayPos.x;
        displayPos.y += maxHeight;
        maxHeight = 0;
    }
}
