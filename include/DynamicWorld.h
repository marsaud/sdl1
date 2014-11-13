#ifndef DYNAMICWORLD_H
#define DYNAMICWORLD_H

#include <string>
#include <vector>
#include <unordered_map>

#include "common.h"
#include "TileSetLoader.h"
#include "ZoneSetLoader.h"
#include "ZoneLinker.h"

class DynamicWorld
{
public:
    DynamicWorld(std::string const& scenario);
    virtual ~DynamicWorld();

    typedef std::vector<Tile> TileSetLine;
    typedef std::vector<DynamicWorld::TileSetLine> TileSet;
    typedef std::vector<std::string> ZoneSetLine;
    typedef std::vector<DynamicWorld::ZoneSetLine> ZoneSet;

    void process(Action & action);
    void move(Move & move);

    std::string getPartyZone() const;
    Position getPartyTile() const;
    DynamicWorld::ZoneSet getZoneSet() const; /** @todo const& overload ? */
    DynamicWorld::TileSet getZone(std::string const& key);
    DynamicWorld::TileSet getZone(Position const& pos);
    const DynamicWorld::TileSet& getZone(std::string const& key) const;
    const DynamicWorld::TileSet& getZone(Position const& pos) const;
protected:
private:
    Movement m_movements[MOVE_LIST_SIZE];

    Position m_partyTile;
    Position m_partyZone;
    std::string m_currentSet;
    ZoneLinker* m_zoneLinker = NULL;
    std::string m_scenario;

    DynamicWorld::ZoneSet m_zoneSet;
    std::unordered_map<std::string,DynamicWorld::TileSet> m_loadedTileSets;

    void m_link(Action & action);

    bool m_outOfSet(Position const& pos, DynamicWorld::TileSet const& tileSet) const;
    bool m_outOfSet(Position const& pos, DynamicWorld::ZoneSet const& zoneSet) const;

    void m_bootScenario(std::string const& scenario);
    void m_loadSet(std::string const& scenario, std::string const& subSet);
};

#endif // DYNAMICWORLD_H
