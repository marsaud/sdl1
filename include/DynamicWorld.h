#ifndef DYNAMICWORLD_H
#define DYNAMICWORLD_H

#include <vector>

#include "common.h"
#include "Party.h"
#include "TileSetLoader.h"

class DynamicWorld
{
public:
    DynamicWorld();
    virtual ~DynamicWorld();

    typedef std::vector<std::vector<Tile> > TileSet;

    Party* getParty() const;
    Position move(Move & move) const;
    Tile getTile(unsigned int const x, unsigned const int y) const;
    DynamicWorld::TileSet getTileSet() const;
protected:
private:
    Party* m_party;
    DynamicWorld::TileSet m_tileSet;

    /** @todo Why private? This could be static or more general...*/
    bool m_move(Move const move, Position & position) const;

};

#endif // DYNAMICWORLD_H
