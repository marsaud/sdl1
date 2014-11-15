#ifndef STATICAREA_H
#define STATICAREA_H

#include <string>
#include <vector>
#include <unordered_map>

#include "common.h"
#include "TileSetLoader.h"
#include "ZoneSetLoader.h"
#include "ZoneLinker.h"

class StaticArea
{
public:
    StaticArea(std::string const& key, std::string const& scenarioDir);
    virtual ~StaticArea();

    typedef std::vector<Tile> TileSetLine;
    typedef std::vector<StaticArea::TileSetLine> TileSet;
    typedef std::vector<std::string> ZoneSetLine;
    typedef std::vector<StaticArea::ZoneSetLine> ZoneSet;
    typedef std::unordered_map<std::string,StaticArea::TileSet> TileSetMapping;

    const StaticArea::ZoneSet& getZoneSet() const;
    StaticArea::TileSet getZone(std::string const& key); /** @todo usefull without const ? */
    StaticArea::TileSet getZone(Position const& pos); /** @todo usefull without const ? */
    const StaticArea::TileSet& getZone(std::string const& key) const;
    const StaticArea::TileSet& getZone(Position const& pos) const;
    const ZoneLinker *getLinker() const;

protected:
private:
    std::string m_key;
    StaticArea::ZoneSet m_zoneSet;
    StaticArea::TileSetMapping m_loadedTileSets;
    ZoneLinker* m_zoneLinker = NULL;

    void m_loadSet(std::string const& scenarioDir);
};

#endif // STATICAREA_H
