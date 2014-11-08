#ifndef DYNAMICWORLD_H
#define DYNAMICWORLD_H

#include <string>
#include <vector>
#include <unordered_map>

#include "common.h"
#include "Party.h"
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

    Party* getParty() const;
    Position move(Move & move);
    Tile getTile(unsigned int const x, unsigned const int y) const;
    DynamicWorld::TileSet getTileSet() const;

    Position getPartyTile() const;
    std::string getPartyZone() const;
    DynamicWorld::ZoneSet getZoneSet() const;
    DynamicWorld::TileSet getZone(std::string const& key);
    DynamicWorld::TileSet getZone(Position const& pos);
    const DynamicWorld::TileSet& getZone(std::string const& key) const;
    const DynamicWorld::TileSet& getZone(Position const& pos) const;
protected:
private:
    Movement m_movements[MOVE_LIST_SIZE];

    Party* m_party;
    Position m_partyTile;
    Position m_partyZone;

    DynamicWorld::TileSet m_tileSet;
    DynamicWorld::ZoneSet m_zoneSet;
    std::unordered_map<std::string,DynamicWorld::TileSet> m_loadedTileSets;

    /** @todo Why private? This could be static or more general...*/
    bool m_move(Move const move, Position & position) const;
    bool m_outOfZone(Position const& pos, DynamicWorld::TileSet const& tileSet) const;
    bool m_outOfZoneSet(Position const& pos, DynamicWorld::ZoneSet const& zoneSet) const;
};

#endif // DYNAMICWORLD_H
