#include "PartyPlayer.h"

Movement* PartyPlayer::ms_movements = NULL;

PartyPlayer::PartyPlayer(StaticWorld *world)
{
    m_area = world->getStartArea();
    const ZoneLinker::ZoneLink *startLink = world->getArea(m_area)->getLinker()->find("start");
    if (NULL == startLink)
    {
        /** @todo throw Exception */
    }

    m_zone = startLink->zone;
    m_tile = startLink->tile;
    m_world = world;
}

PartyPlayer::~PartyPlayer()
{
    //dtor
}

void PartyPlayer::init()
{
    ms_movements = new Movement[MOVE_LIST_SIZE];

    ms_movements[MOVE_NOT] = {0,0};
    ms_movements[MOVE_RIGHT] = {1,0};
    ms_movements[MOVE_LEFT] = {-1,0};
    ms_movements[MOVE_UP] = {0,-1};
    ms_movements[MOVE_DOWN] = {0,1};
}

void PartyPlayer::free()
{
    delete[] ms_movements;
    ms_movements = NULL;
}

void PartyPlayer::process(Action & action)
{
    switch (action)
    {
    case ACTION_ENTER_ZONE:
        m_link(action);
        break;
    default:
        action = ACTION_NONE;
        break;
    }
}

void PartyPlayer::m_link(Action & action)
{
    const ZoneLinker::ZoneLink* zLink = m_world->getArea(m_area)->getLinker()->find(m_zone, m_tile);
    if ((NULL != zLink) && ("#" != zLink->targetSet))
    {
            const ZoneLinker* targetLinker = m_world->getArea(zLink->targetSet)->getLinker();
            const ZoneLinker::ZoneLink* targetLink = targetLinker->find(zLink->targetLinkTag);
            if (NULL != targetLink)
            {
                m_area = zLink->targetSet;
                m_zone = targetLink->zone;
                m_tile = targetLink->tile;
            }
            else
            {
                action = ACTION_NONE;
            }
    }
    else
    {
        action = ACTION_NONE;
    }
}

void PartyPlayer::move(Move & move)
{
    if (MOVE_NOT != move)
    {
        Position previewTile = m_tile;
        Position previewZone = m_zone;
        previewTile += ms_movements[move];

        if (m_outOfSet(previewTile, m_world->getArea(m_area)->getZone(m_zone)))
        {
            previewZone += ms_movements[move];
            if (m_outOfSet(previewZone, m_world->getArea(m_area)->getZoneSet()))
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
                    previewTile.x = m_world->getArea(m_area)->getZone(previewZone)[previewTile.y].size() - 1;
                    break;
                case MOVE_UP:
                    previewTile.y = m_world->getArea(m_area)->getZone(previewZone).size() - 1;
                    break;
                default:
                    break;
                }

                if (m_outOfSet(previewTile, m_world->getArea(m_area)->getZone(m_zone)))
                {
                    move = MOVE_NOT;
                }
            }
        }

        if (MOVE_NOT != move)
        {
            Tile tile = m_world->getArea(m_area)->getZone(previewZone)[previewTile.y][previewTile.x];
            switch (tile)
            {
            case TILE_CAVE:
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
                m_zone = previewZone;
                m_tile = previewTile;
            }
        }
    }
}

bool PartyPlayer::m_outOfSet(Position const& pos, PartyPlayer::TileSet const& tileSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= tileSet.size()) || (pos.x >= tileSet[pos.y].size()));
}

bool PartyPlayer::m_outOfSet(Position const& pos, PartyPlayer::ZoneSet const& zoneSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= zoneSet.size()) || (pos.x >= zoneSet[pos.y].size()));
}

