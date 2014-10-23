#ifndef TILESETLOADER_H
#define TILESETLOADER_H

#include "common.h"
#include <vector>
#include <fstream>

class TileSetLoader
{
    public:
        TileSetLoader();
        virtual ~TileSetLoader();
        bool load(std::vector<std::vector<Tile> >& tileSet);
    protected:
    private:
};

#endif // TILESETLOADER_H
