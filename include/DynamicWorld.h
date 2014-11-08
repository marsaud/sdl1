#ifndef DYNAMICWORLD_H
#define DYNAMICWORLD_H

#include <string>
#include <vector>
#include <unordered_map>

#include "common.h"
#include "TileSetLoader.h"
#include "ZoneSetLoader.h"

class DynamicWorld
{
public:
    DynamicWorld();
    virtual ~DynamicWorld();

    typedef std::vector<Tile> TileSetLine;
    typedef std::vector<DynamicWorld::TileSetLine> TileSet;
    typedef std::vector<std::string> ZoneSetLine;
    typedef std::vector<DynamicWorld::ZoneSetLine> ZoneSet;

    void move(Move & move);

    std::string getPartyZone() const;
    Position getPartyTile() const;
    DynamicWorld::ZoneSet getZoneSet() const;
    DynamicWorld::TileSet getZone(std::string const& key);
    DynamicWorld::TileSet getZone(Position const& pos);
    const DynamicWorld::TileSet& getZone(std::string const& key) const;
    const DynamicWorld::TileSet& getZone(Position const& pos) const;
protected:
private:
    Movement m_movements[MOVE_LIST_SIZE];

    Position m_partyTile;
    Position m_partyZone;

    DynamicWorld::ZoneSet m_zoneSet;
    std::unordered_map<std::string,DynamicWorld::TileSet> m_loadedTileSets;

    bool m_outOfSet(Position const& pos, DynamicWorld::TileSet const& tileSet) const;
    bool m_outOfSet(Position const& pos, DynamicWorld::ZoneSet const& zoneSet) const;
};

#endif // DYNAMICWORLD_H
