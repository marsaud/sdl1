#ifndef TILESETLOADER_H
#define TILESETLOADER_H

#include <vector>
#include <fstream>

#include "common.h"

class TileSetLoader
{
public:
    TileSetLoader();
    virtual ~TileSetLoader();

    typedef std::vector<std::vector<Tile> > TileSet;

    bool load(std::string const& tileMapPath, TileSetLoader::TileSet & tileSet) const;
protected:
private:
    enum DataFileChar {DIRT = 'd', FOREST = 'f', GRASS = 'g', HILL = 'h', MOUNT = 'm', WATER = 'w', LINE_BREAK = '\n'};
};

#endif // TILESETLOADER_H
