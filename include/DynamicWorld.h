#ifndef DYNAMICWORLD_H
#define DYNAMICWORLD_H

#include "Party.h"
#include <vector>
#include "common.h"
#include "TileSetLoader.h"

class DynamicWorld
{
    public:
        DynamicWorld();
        virtual ~DynamicWorld();

        Party* getParty() const;
        Position move(Move move);
        Tile getTile(unsigned int x, unsigned int y) const;

        std::vector<std::vector<Tile> > getTileSet() const;
    protected:
    private:
        Party* m_party;
        std::vector<std::vector<Tile> > m_tileSet;

        bool m_move(Move move, Position & position);

};

#endif // DYNAMICWORLD_H
