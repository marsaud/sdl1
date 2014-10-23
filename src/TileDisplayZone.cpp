#include "TileDisplayZone.h"

TileDisplayZone::TileDisplayZone(Sint16 displayZoneLeft, Sint16 displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
    m_tiles = new SDL_Surface*[TILE_LIST_SIZE];

    m_tiles[TILE_DIRT] = IMG_Load("images/dirt.png");
    m_tiles[TILE_FOREST] = IMG_Load("images/forest.png");
    m_tiles[TILE_GRASS] = IMG_Load("images/grass.png");
    m_tiles[TILE_HILL] = IMG_Load("images/hills.png");
    m_tiles[TILE_MOUNT] = IMG_Load("images/mount.png");
    m_tiles[TILE_WATER] = IMG_Load("images/water.png");
    m_tiles[TILE_NONE] = IMG_Load("images/warrior.png");
}

TileDisplayZone::~TileDisplayZone()
{
    for (int i = 0;i < TILE_LIST_SIZE;++i)
    {
        SDL_FreeSurface(m_tiles[i]);
    }

    delete[] m_tiles;
}

void TileDisplayZone::render(DynamicWorld const& world, SDL_Surface* screen) const
{
    SDL_Rect displayPos = m_displayPos;

    std::vector<std::vector<Tile> > tileSet = world.getTileSet();

    for (std::vector<std::vector<Tile> >::iterator yit = tileSet.begin(); tileSet.end() != yit; ++yit)
    {
        for (std::vector<Tile>::iterator xit = yit->begin(); yit->end() != xit; ++xit)
        {
            SDL_BlitSurface(m_tiles[*xit], NULL, screen, &displayPos);
            displayPos.x += 30;
        }
        displayPos.x = m_displayPos.x;
        displayPos.y += 30;
    }

    displayPos.x = 30 * world.getParty()->getPosition().x;
    displayPos.y = 30 * world.getParty()->getPosition().y;

    SDL_BlitSurface(m_tiles[TILE_NONE], NULL, screen, &displayPos);
}
