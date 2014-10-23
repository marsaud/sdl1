#include "DynamicWorld.h"

DynamicWorld::DynamicWorld()
{
    m_party = new Party;

    TileSetLoader* loader = new TileSetLoader;
    loader->load(m_tileSet);
    delete loader;
}

DynamicWorld::~DynamicWorld()
{
    delete m_party;
}

Party* DynamicWorld::getParty() const
{
    return m_party;
}

Position DynamicWorld::move(Move move)
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

Tile DynamicWorld::getTile(unsigned int x, unsigned int y) const
{
    if ((m_tileSet.size() < y) || (m_tileSet[y].size() < x))
    {
        return TILE_NONE;
    }
    else
    {
        return m_tileSet[y][x];
    }
}

std::vector<std::vector<Tile> > DynamicWorld::getTileSet() const
{
    return m_tileSet;
}

bool DynamicWorld::m_move(Move move, Position& position)
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
