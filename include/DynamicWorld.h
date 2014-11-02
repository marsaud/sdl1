#ifndef DYNAMICWORLD_H
#define DYNAMICWORLD_H

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

    typedef std::vector<std::vector<Tile> > TileSet;
    typedef std::vector<std::vector<std::string> > ZoneSet;

    Party* getParty() const;
    Position move(Move & move) const;
    Tile getTile(unsigned int const x, unsigned const int y) const;
    DynamicWorld::TileSet getTileSet() const;

    Position getPartyTile() const;
    std::string getPartyZone() const;
    DynamicWorld::ZoneSet getZoneSet() const;
    DynamicWorld::TileSet getZone(std::string const& key) /** @todo const*/;
protected:
private:
    Party* m_party;
    Position m_partyTile;
    std::string m_partyZone;

    DynamicWorld::TileSet m_tileSet;
    DynamicWorld::ZoneSet m_zoneSet;
    std::unordered_map<std::string,DynamicWorld::TileSet> m_loadedTileSets;

    /** @todo Why private? This could be static or more general...*/
    bool m_move(Move const move, Position & position) const;

};

#endif // DYNAMICWORLD_H
