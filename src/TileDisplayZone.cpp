#include "TileDisplayZone.h"

TileDisplayZone::TileDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
    m_tiles = new SDL_Surface*[TILE_LIST_SIZE];

    m_tiles[TILE_DIRT] = IMG_Load("images/dirt.png");
    m_tiles[TILE_FOREST] = IMG_Load("images/forest.png");
    m_tiles[TILE_GRASS] = IMG_Load("images/grass.png");
    m_tiles[TILE_HILL] = IMG_Load("images/hills.png");
    m_tiles[TILE_MOUNT] = IMG_Load("images/mount.png");
    m_tiles[TILE_WATER] = IMG_Load("images/water.png");
    /** @todo Temporary */
    m_tiles[TILE_NONE] = IMG_Load("images/warrior.png");

    m_computeTileMask();
}

TileDisplayZone::~TileDisplayZone()
{
    for (int i = 0;i < TILE_LIST_SIZE;++i)
    {
        SDL_FreeSurface(m_tiles[i]);
    }

    delete[] m_tiles;
}

void TileDisplayZone::render(SDL_Surface* screen, DynamicWorld const& world) const
{
    SDL_Rect displayPos = m_displayPos;

    std::vector<std::vector<Tile> > tileSet = world.getTileSet();

    for (std::vector<std::vector<Tile> >::iterator yit = tileSet.begin(); tileSet.end() != yit; ++yit)
    {
        for (std::vector<Tile>::iterator xit = yit->begin(); yit->end() != xit; ++xit)
        {
            SDL_BlitSurface(m_tiles[*xit], NULL, screen, &displayPos);
            displayPos.x += m_tileMask.w;
        }
        displayPos.x = m_displayPos.x;
        displayPos.y += m_tileMask.h;
    }

    /** @todo Temporary */
    displayPos.x = m_tileMask.w * world.getParty()->getPosition().x;
    displayPos.y = m_tileMask.h * world.getParty()->getPosition().y;
    SDL_BlitSurface(m_tiles[TILE_NONE], NULL, screen, &displayPos);
}

void TileDisplayZone::m_computeTileMask()
{
    m_tileMask = {0,0};
    for (int i = 0;i < TILE_LIST_SIZE;i++)
    {
        (m_tileMask.w >= m_tiles[i]->w) || (m_tileMask.w = m_tiles[i]->w);
        (m_tileMask.h >= m_tiles[i]->h) || (m_tileMask.h = m_tiles[i]->h);
    }
}
