#include "DynamicWorld.h"

DynamicWorld::DynamicWorld()
{
    m_party = new Party;

    m_partyTile = {0,0};
    m_partyZone = "a";

    ZoneSetLoader* zLoader = new ZoneSetLoader;
    zLoader->load("data/scenario1/zonemap.txt", m_zoneSet);
    delete zLoader;

    TileSetLoader* tLoader = new TileSetLoader;
    for(ZoneSet::iterator yit = m_zoneSet.begin(); m_zoneSet.end() != yit; ++yit)
    {
        for(std::vector<std::string>::iterator xit = yit->begin(); yit->end() != xit; ++xit)
        {
            DynamicWorld::TileSet tileSet;
            tLoader->load("data/scenario1/" + *xit + ".tm", tileSet);
            m_loadedTileSets[*xit] = tileSet;
        }
    }
    tLoader->load("data/scenario1/tilemap.txt", m_tileSet);
    delete tLoader;
}

DynamicWorld::~DynamicWorld()
{
    delete m_party;
}

Party* DynamicWorld::getParty() const
{
    return m_party;
}

Position DynamicWorld::move(Move & move) const
{
    Position position = m_party->getPosition();

    if (m_move(move, position))
    {
        Tile tile = getTile(position.x, position.y);
        switch (tile)
        {
        case TILE_MOUNT:
        case TILE_WATER:
        case TILE_NONE:
            move = MOVE_NOT;
            break;
        default:
            break;
        }
    }
    else
    {
        move = MOVE_NOT;
    }

    return m_party->move(move);
}

Tile DynamicWorld::getTile(unsigned int const x, unsigned int const y) const
{
    if ((m_tileSet.size() <= y) || (m_tileSet[y].size() <= x))
    {
        return TILE_NONE;
    }
    else
    {
        return m_tileSet[y][x];
    }
}

DynamicWorld::TileSet DynamicWorld::getTileSet() const
{
    return m_tileSet;
}

bool DynamicWorld::m_move(Move const move, Position& position) const
{
    bool moved = false;
    switch (move)
    {
    case MOVE_DOWN:
        moved = true;
        position.y++;
        break;
    case MOVE_LEFT:
        moved = position.x > 0;
        moved && position.x--;
        break;
    case MOVE_NOT:
        break;
    case MOVE_RIGHT:
        moved = true;
        position.x++;
        break;
    case MOVE_UP:
        moved = position.y > 0;
        moved && position.y--;
        break;
    default:
        break;
    }

    return moved;
}

DynamicWorld::ZoneSet DynamicWorld::getZoneSet() const
{
    return m_zoneSet;
}

DynamicWorld::TileSet DynamicWorld::getZone(std::string const& key) /** @todo const*/
{
    return m_loadedTileSets[key];
}

Position DynamicWorld::getPartyTile() const
{
    return m_partyTile;
}

std::string DynamicWorld::getPartyZone() const
{
    return m_partyZone;
}
