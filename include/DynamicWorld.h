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
        Tile m_tileSet[5][5];

};

#endif // DYNAMICWORLD_H
