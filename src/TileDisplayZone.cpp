#include "TileDisplayZone.h"

SDL_Surface** TileDisplayZone::ms_tiles = NULL;
SDL_Rect TileDisplayZone::ms_tileMask = {0,0};

void TileDisplayZone::init()
{
    ms_loadTiles();
    ms_computeTileMask();
}

void TileDisplayZone::ms_loadTiles()
{
    ms_tiles = new SDL_Surface*[TILE_LIST_SIZE];

    ms_tiles[TILE_DIRT] = IMG_Load("images/dirt.png");
    ms_tiles[TILE_FOREST] = IMG_Load("images/forest.png");
    ms_tiles[TILE_GRASS] = IMG_Load("images/grass.png");
    ms_tiles[TILE_HILL] = IMG_Load("images/hills.png");
    ms_tiles[TILE_MOUNT] = IMG_Load("images/mount.png");
    ms_tiles[TILE_WATER] = IMG_Load("images/water.png");
    /** @todo Temporary */
    ms_tiles[TILE_NONE] = IMG_Load("images/warrior.png");
}

void TileDisplayZone::ms_computeTileMask()
{
    for (int i = 0; i < TILE_LIST_SIZE; i++)
    {
        (ms_tileMask.w >= ms_tiles[i]->w) || (ms_tileMask.w = ms_tiles[i]->w);
        (ms_tileMask.h >= ms_tiles[i]->h) || (ms_tileMask.h = ms_tiles[i]->h);
    }
}

void TileDisplayZone::free()
{
    for (int i = 0; i < TILE_LIST_SIZE; ++i)
    {
        SDL_FreeSurface(ms_tiles[i]);
    }

    delete[] ms_tiles;
    ms_tiles = NULL;
}

TileDisplayZone::TileDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
}

TileDisplayZone::~TileDisplayZone()
{
    //dtor
}

SDL_Rect TileDisplayZone::render(SDL_Surface* screen, TileDisplayZone::TileSet const& tileSet) const
{
    SDL_Rect displayPos = m_displayPos;
    SDL_Rect finalSize = {0,0,0,0};
    Uint16 tileNumWidth = 0;
    Uint16 maxTileNumWidth = 0;
    Uint16 tileNumHeight = 0;

    for (TileDisplayZone::TileSet::const_iterator yit = tileSet.cbegin(); tileSet.cend() != yit; ++yit)
    {
        tileNumHeight++;

        for (TileDisplayZone::TileSetLine::const_iterator xit = yit->cbegin(); yit->cend() != xit; ++xit)
        {
            tileNumWidth++;

            SDL_BlitSurface(ms_tiles[*xit], NULL, screen, &displayPos);
            displayPos.x += ms_tileMask.w;
        }

        (tileNumWidth <= maxTileNumWidth) || (maxTileNumWidth = tileNumWidth);
        tileNumWidth = 0;

        displayPos.x = m_displayPos.x;
        displayPos.y += ms_tileMask.h;
    }

    finalSize.w = maxTileNumWidth * ms_tileMask.w;
    finalSize.h = tileNumHeight * ms_tileMask.h;

    return finalSize;
}

SDL_Rect TileDisplayZone::render(SDL_Surface* screen, Position tilePos, Tile tile) const
{
    SDL_Rect displayPos = {tilePos.x * ms_tileMask.w + m_displayPos.x, tilePos.y * ms_tileMask.h + m_displayPos.y};
    SDL_BlitSurface(ms_tiles[tile], NULL, screen, &displayPos);

    return displayPos;
}
