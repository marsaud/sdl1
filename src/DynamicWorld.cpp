#include "DynamicWorld.h"

DynamicWorld::DynamicWorld()
{
    m_party = new Party;

    m_movements[MOVE_NOT] = {0,0};
    m_movements[MOVE_RIGHT] = {1,0};
    m_movements[MOVE_LEFT] = {-1,0};
    m_movements[MOVE_DOWN] = {0,1};
    m_movements[MOVE_UP] = {0,-1};

    m_partyTile = {0,0};
    m_partyZone = {0,0};

    ZoneSetLoader* zLoader = new ZoneSetLoader;
    zLoader->load("data/scenario1/zonemap.txt", m_zoneSet);
    delete zLoader;

    TileSetLoader* tLoader = new TileSetLoader;
    for(DynamicWorld::ZoneSet::iterator yit = m_zoneSet.begin(); m_zoneSet.end() != yit; ++yit)
    {
        for(DynamicWorld::ZoneSetLine::iterator xit = yit->begin(); yit->end() != xit; ++xit)
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

Position DynamicWorld::move(Move & move)
{
    Move moveCopy = move;/** @todo OLD WAY */

    if (MOVE_NOT != move)
    {
        Position previewTile = m_partyTile;
        Position previewZone = m_partyZone;
        previewTile += m_movements[move];

        if (m_outOfZone(previewTile, getZone(getPartyZone())))
        {
            previewZone += m_movements[move];
            if (m_outOfZoneSet(previewZone, m_zoneSet))
            {
                move = MOVE_NOT;
            }
            else
            {
                switch(move)
                {
                case MOVE_RIGHT:
                    previewTile.x = 0;
                    break;
                case MOVE_DOWN:
                    previewTile.y = 0;
                    break;
                case MOVE_LEFT:
                    previewTile.x = getZone(previewZone)[previewTile.y].size() - 1;
                    break;
                case MOVE_UP:
                    previewTile.y = getZone(previewZone).size() - 1;
                    break;
                default:
                    break;
                }

                if (m_outOfZone(previewTile, getZone(getPartyZone())))
                {
                    move = MOVE_NOT;
                }
            }
        }

        if (MOVE_NOT != move)
        {
            Tile tile = getZone(previewZone)[previewTile.y][previewTile.x];
            switch (tile)
            {
            case TILE_DIRT:
            case TILE_FOREST:
            case TILE_GRASS:
            case TILE_HILL:
                break;

            case TILE_MOUNT:
            case TILE_WATER:
            case TILE_NONE:
            default:
                move = MOVE_NOT;
                break;

            }

            if (MOVE_NOT != move)
            {
                m_partyZone = previewZone;
                m_partyTile = previewTile;
            }
        }

    }

    /**
    * old way
    */
    Position position = m_party->getPosition();

    if (m_move(moveCopy, position))
    {
        Tile tile = getTile(position.x, position.y);
        switch (tile)
        {
        case TILE_MOUNT:
        case TILE_WATER:
        case TILE_NONE:
            moveCopy = MOVE_NOT;
            break;
        default:
            break;
        }
    }
    else
    {
        moveCopy = MOVE_NOT;
    }

    return m_party->move(moveCopy);
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

DynamicWorld::TileSet DynamicWorld::getZone(std::string const& key)
{
    return m_loadedTileSets.at(key);
}

const DynamicWorld::TileSet& DynamicWorld::getZone(std::string const& key) const
{
    return m_loadedTileSets.at(key);
}

DynamicWorld::TileSet DynamicWorld::getZone(Position const& pos)
{
    return m_loadedTileSets.at(m_zoneSet[pos.y][pos.x]);
}

const DynamicWorld::TileSet& DynamicWorld::getZone(Position const& pos) const
{
    return m_loadedTileSets.at(m_zoneSet[pos.y][pos.x]);
}

Position DynamicWorld::getPartyTile() const
{
    return m_partyTile;
}

std::string DynamicWorld::getPartyZone() const
{
    return m_zoneSet[m_partyZone.y][m_partyZone.x];
}

bool DynamicWorld::m_outOfZone(Position const& pos, DynamicWorld::TileSet const& tileSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= tileSet.size()) || (pos.x >= tileSet[pos.y].size()));
}

bool DynamicWorld::m_outOfZoneSet(Position const& pos, DynamicWorld::ZoneSet const& zoneSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= zoneSet.size()) || (pos.x >= zoneSet[pos.y].size()));
}
