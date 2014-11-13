#include "DynamicWorld.h"

DynamicWorld::DynamicWorld(std::string const& scenario)
{
    /** @todo to be moved */
    m_movements[MOVE_NOT] = {0,0};
    m_movements[MOVE_RIGHT] = {1,0};
    m_movements[MOVE_LEFT] = {-1,0};
    m_movements[MOVE_DOWN] = {0,1};
    m_movements[MOVE_UP] = {0,-1};

    m_bootScenario(scenario);
}

DynamicWorld::~DynamicWorld()
{
    delete m_zoneLinker;
}

void DynamicWorld::m_loadSet(std::string const& scenario, std::string const& subSet)
{
    m_zoneSet.clear();

    ZoneSetLoader* zLoader = new ZoneSetLoader;
    zLoader->load("data/" + scenario + "/" + subSet + "/zonemap.zm", m_zoneSet);
    delete zLoader;

    TileSetLoader* tLoader = new TileSetLoader;
    for(DynamicWorld::ZoneSet::iterator yit = m_zoneSet.begin(); m_zoneSet.end() != yit; ++yit)
    {
        for(DynamicWorld::ZoneSetLine::iterator xit = yit->begin(); yit->end() != xit; ++xit)
        {
            DynamicWorld::TileSet tileSet;
            tLoader->load("data/" + scenario + "/" + subSet + "/" + *xit + ".tm", tileSet);
            m_loadedTileSets[*xit] = tileSet;
        }
    }
    delete tLoader;
}

void DynamicWorld::move(Move & move)
{
    if (MOVE_NOT != move)
    {
        Position previewTile = m_partyTile;
        Position previewZone = m_partyZone;
        previewTile += m_movements[move];

        if (m_outOfSet(previewTile, getZone(getPartyZone())))
        {
            previewZone += m_movements[move];
            if (m_outOfSet(previewZone, m_zoneSet))
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

                if (m_outOfSet(previewTile, getZone(getPartyZone())))
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
                m_partyZone = previewZone;
                m_partyTile = previewTile;
            }
        }
    }
}

void DynamicWorld::process(Action & action)
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

void DynamicWorld::m_link(Action & action)
{
    const ZoneLinker::ZoneLink* zLink = m_zoneLinker->find(m_partyZone, m_partyTile);

    if ((NULL != zLink) && ("#" != zLink->targetSet))
    {
        if (zLink->targetSet != m_currentSet)
        {
            ZoneLinker* targetLinker = new ZoneLinker("data/" + m_scenario + "/" + zLink->targetSet + "/zone.links");
            const ZoneLinker::ZoneLink* targetLink = targetLinker->find(zLink->targetLinkTag);
            if (NULL != targetLink)
            {
                /** @todo load zoneSet & tileSet */
                m_loadSet(m_scenario, zLink->targetSet);

                m_currentSet = zLink->targetSet;
                m_partyZone = targetLink->zone;
                m_partyTile = targetLink->tile;

                delete m_zoneLinker;
                m_zoneLinker = targetLinker;
            }
            else
            {
                delete targetLinker;
                action = ACTION_NONE;
            }
        }
        else
        {
            const ZoneLinker::ZoneLink* targetLink = m_zoneLinker->find(zLink->targetLinkTag);
            if (NULL != targetLink)
            {
                m_partyZone = targetLink->zone;
                m_partyTile = targetLink->tile;
            }
            else
            {
                action = ACTION_NONE;
            }
        }
    }
    else
    {
        action = ACTION_NONE;
    }
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
    return getZone(m_zoneSet[pos.y][pos.x]);
}

const DynamicWorld::TileSet& DynamicWorld::getZone(Position const& pos) const
{
    return getZone(m_zoneSet[pos.y][pos.x]);
}

Position DynamicWorld::getPartyTile() const
{
    return m_partyTile;
}

std::string DynamicWorld::getPartyZone() const
{
    return m_zoneSet[m_partyZone.y][m_partyZone.x];
}

bool DynamicWorld::m_outOfSet(Position const& pos, DynamicWorld::TileSet const& tileSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= tileSet.size()) || (pos.x >= tileSet[pos.y].size()));
}

bool DynamicWorld::m_outOfSet(Position const& pos, DynamicWorld::ZoneSet const& zoneSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= zoneSet.size()) || (pos.x >= zoneSet[pos.y].size()));
}

void DynamicWorld::m_bootScenario(std::string const& scenario)
{
    std::ifstream dataFile("data/" + scenario + "/boot.scn");
    std::string line;

    /** @todo All here is to secure */

    while(std::getline(dataFile, line))
    {
        /** @todo share */
        if ('\r' == *(line.cend()-1))
        {
            line.erase(line.end()-1);
        }

        std::stringstream streamLine(line);
        std::string word;

        streamLine >> word;
        if ("start" == word)
        {
            streamLine >> word;
            ZoneLinker* linker = new ZoneLinker("data/" + scenario + "/" + word + "/zone.links");
            const ZoneLinker::ZoneLink* startLink = linker->find("start");
            if (NULL != startLink)
            {
                /** @todo check for coherence */

                m_loadSet(scenario, word);

                m_currentSet = word;
                m_partyZone = startLink->zone;
                m_partyTile = startLink->tile;
                m_zoneLinker = linker;

                m_scenario = scenario;
            }
            else
            {
                /** @todo throw exception */
            }
        }
        else
        {
            /** @todo throw exception */
        }
    }

    dataFile.close();
}
