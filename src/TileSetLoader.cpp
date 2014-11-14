#include "TileSetLoader.h"

const std::string TileSetLoader::TILEMAP_FILE_EXT = "tm";

TileSetLoader::TileSetLoader()
{
    //ctor
}

TileSetLoader::~TileSetLoader()
{
    //dtor
}

bool TileSetLoader::load(std::string const& tileMapPath, TileSetLoader::TileSet & tileSet) const
{
    std::ifstream tileFile(tileMapPath);

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
                tileSet.push_back(TileSetLoader::TileSetLine(0));
            }

            switch (tileChar)
            {
            case TileSetLoader::CAVE:
                tile = TILE_CAVE;
                break;
            case TileSetLoader::DIRT:
                tile = TILE_DIRT;
                break;
            case TileSetLoader::GRASS:
                tile = TILE_GRASS;
                break;
            case TileSetLoader::FOREST:
                tile = TILE_FOREST;
                break;
            case TileSetLoader::HILL:
                tile = TILE_HILL;
                break;
            case TileSetLoader::MOUNT:
                tile = TILE_MOUNT;
                break;
            case TileSetLoader::WATER:
                tile = TILE_WATER;
                break;
            default:
                tile = TILE_NONE;
                break;
            }

            switch (tileChar)
            {
            case TileSetLoader::CAVE:
            case TileSetLoader::DIRT:
            case TileSetLoader::GRASS:
            case TileSetLoader::FOREST:
            case TileSetLoader::HILL:
            case TileSetLoader::WATER:
            case TileSetLoader::MOUNT:
                tileSet.rbegin()->push_back(tile);
                break;
            case TileSetLoader::LINE_BREAK:
                tileSet.push_back(TileSetLoader::TileSetLine(0));
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
