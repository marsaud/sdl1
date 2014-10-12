#include "TileDisplayZone.h"

TileDisplayZone::TileDisplayZone(Sint16 displayZoneLeft, Sint16 displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
    m_tiles = new SDL_Surface*[6];

    m_tiles[TILE_DIRT] = IMG_Load("dirt.png");
    m_tiles[TILE_FOREST] = IMG_Load("forest.png");
    m_tiles[TILE_GRASS] = IMG_Load("grass.png");
    m_tiles[TILE_HILL] = IMG_Load("hills.png");
    m_tiles[TILE_MOUNT] = IMG_Load("mount.png");
    m_tiles[TILE_WATER] = IMG_Load("water.png");
}

TileDisplayZone::~TileDisplayZone()
{
    for (int i = 0;i < 6;++i)
    {
        SDL_FreeSurface(m_tiles[i]);
    }

    delete[] m_tiles;
}

void TileDisplayZone::render(DynamicWorld const& world, int tileSetWidth, int tileSetHeight, SDL_Surface* screen) const
{
    SDL_Rect displayPos = m_displayPos;

    for (int x = 0;x < tileSetWidth;++x)
    {
        for (int y = 0;y < tileSetHeight;++y)
        {
            SDL_BlitSurface(m_tiles[world.getTile(x,y)], NULL, screen, &displayPos);
            displayPos.y += 30;
        }
        displayPos.y = m_displayPos.y;
        displayPos.x += 30;
    }
}
