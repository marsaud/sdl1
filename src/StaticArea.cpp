#include "StaticArea.h"

StaticArea::StaticArea(std::string const& key, std::string const& scenarioDir)
{
    m_zoneLinker = new ZoneLinker(scenarioDir + "/" + key + "/" + ZoneLinker::ZONE_LINK_FILE);
    m_loadSet(scenarioDir + "/" + key);
    m_key = key;
}

StaticArea::~StaticArea()
{
    delete m_zoneLinker;
    m_loadedTileSets.clear();
    m_zoneSet.clear();
}

void StaticArea::m_loadSet(std::string const& areaDir)
{
    m_zoneSet.clear();

    ZoneSetLoader* zLoader = new ZoneSetLoader;
    zLoader->load(areaDir + "/" + ZoneSetLoader::ZONESET_FILE, m_zoneSet);
    delete zLoader;

    TileSetLoader* tLoader = new TileSetLoader;
    for(StaticArea::ZoneSet::iterator yit = m_zoneSet.begin(); m_zoneSet.end() != yit; ++yit) /** @todo const_iterator ? */
    {
        for(StaticArea::ZoneSetLine::iterator xit = yit->begin(); yit->end() != xit; ++xit)
        {
            StaticArea::TileSet tileSet;
            tLoader->load(areaDir + "/" + *xit + "." + TileSetLoader::TILEMAP_FILE_EXT, tileSet);
            m_loadedTileSets[*xit] = tileSet;
        }
    }
    delete tLoader;
}

const StaticArea::ZoneSet& StaticArea::getZoneSet() const /** @todo const overload ? */
{
    return m_zoneSet;
}

StaticArea::TileSet StaticArea::getZone(std::string const& key)
{
    return m_loadedTileSets.at(key);
}

StaticArea::TileSet StaticArea::getZone(Position const& pos)
{
    return getZone(m_zoneSet[pos.y][pos.x]);
}

const StaticArea::TileSet& StaticArea::getZone(std::string const& key) const
{
    return m_loadedTileSets.at(key);
}

const StaticArea::TileSet& StaticArea::getZone(Position const& pos) const
{
    return getZone(m_zoneSet[pos.y][pos.x]);
}

const ZoneLinker *StaticArea::getLinker() const
{
    return m_zoneLinker;
}
