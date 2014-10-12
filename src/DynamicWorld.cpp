#include "DynamicWorld.h"

#include "Party.h"

DynamicWorld::DynamicWorld()
{
    m_party = new Party;

    m_tileSet[0][0] = TILE_FOREST;
    m_tileSet[0][1] = TILE_FOREST;
    m_tileSet[0][2] = TILE_GRASS;
    m_tileSet[0][3] = TILE_GRASS;
    m_tileSet[0][4] = TILE_HILL;

    m_tileSet[1][0] = TILE_FOREST;
    m_tileSet[1][1] = TILE_GRASS;
    m_tileSet[1][2] = TILE_WATER;
    m_tileSet[1][3] = TILE_WATER;
    m_tileSet[1][4] = TILE_HILL;

    m_tileSet[2][0] = TILE_DIRT;
    m_tileSet[2][1] = TILE_GRASS;
    m_tileSet[2][2] = TILE_WATER;
    m_tileSet[2][3] = TILE_GRASS;
    m_tileSet[2][4] = TILE_HILL;

    m_tileSet[3][0] = TILE_DIRT;
    m_tileSet[3][1] = TILE_GRASS;
    m_tileSet[3][2] = TILE_GRASS;
    m_tileSet[3][3] = TILE_GRASS;
    m_tileSet[3][4] = TILE_MOUNT;

    m_tileSet[4][0] = TILE_DIRT;
    m_tileSet[4][1] = TILE_DIRT;
    m_tileSet[4][2] = TILE_GRASS;
    m_tileSet[4][3] = TILE_HILL;
    m_tileSet[4][4] = TILE_MOUNT;
}

DynamicWorld::~DynamicWorld()
{
    delete m_party;
}

Party* DynamicWorld::getParty() const
{
    return m_party;
}

Tile DynamicWorld::getTile(int x, int y) const
{
    return m_tileSet[x][y];
}
