#include "TileSetLoader.h"

TileSetLoader::TileSetLoader()
{
    //ctor
}

TileSetLoader::~TileSetLoader()
{
    //dtor
}

bool TileSetLoader::load(std::vector<std::vector<Tile> > &tileSet)
{
    std::ifstream tileFile("data/tilemap.txt");

    if (!tileFile)
    {
        return false;
    }
    else
    {
        tileSet.clear();

        char tileChar;
        Tile tile;
        while(tileFile.get(tileChar))
        {
            if (0 == tileSet.size())
            {
                tileSet.push_back(std::vector<Tile>(0));
            }

            switch (tileChar)
            {
            case 'd':
                tile = TILE_DIRT;
                break;
            case 'g':
                tile = TILE_GRASS;
                break;
            case 'f':
                tile = TILE_FOREST;
                break;
            case 'h':
                tile = TILE_HILL;
                break;
            case 'w':
                tile = TILE_WATER;
                break;
            case 'm':
                tile = TILE_MOUNT;
                break;
            default:
                tile = TILE_NONE;
                break;
            }

            switch (tileChar)
            {
            case 'd':
            case 'g':
            case 'h':
            case 'w':
            case 'm':
            case 'f':
                tileSet.rbegin()->push_back(tile);
                break;
            case '\n':
                tileSet.push_back(std::vector<Tile>(0));
                break;
            case '\r':
                break;
            default:
                tileSet.rbegin()->push_back(TILE_NONE);
                break;
            }

        }

        tileFile.close();
        return true;
    }
}
