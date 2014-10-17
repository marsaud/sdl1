#ifndef DYNAMICWORLD_H
#define DYNAMICWORLD_H

#include "Party.h"
#include <vector>
#include "common.h"

class DynamicWorld
{
    public:
        DynamicWorld();
        virtual ~DynamicWorld();
        Party* getParty() const;
        Tile getTile(int x, int y) const;
    protected:
    private:
        Party* m_party;
        std::vector<std::vector<Tile> > m_tileSet;

};

#endif // DYNAMICWORLD_H
