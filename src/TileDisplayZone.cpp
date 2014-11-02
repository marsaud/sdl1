#include "TileDisplayZone.h"

TileDisplayZone::TileDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};

    /** @todo load images out of this object !! Or make it static...*/
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

SDL_Rect TileDisplayZone::render(SDL_Surface* screen, DynamicWorld const& world) const
{
    SDL_Rect displayPos = m_displayPos;

    SDL_Rect finalSize = render(screen, world.getTileSet());

    /** @todo Temporary */
    displayPos.x = m_tileMask.w * world.getParty()->getPosition().x + m_displayPos.x;
    displayPos.y = m_tileMask.h * world.getParty()->getPosition().y + m_displayPos.y;
    SDL_BlitSurface(m_tiles[TILE_NONE], NULL, screen, &displayPos);

    return finalSize;
}

SDL_Rect TileDisplayZone::render(SDL_Surface* screen, DynamicWorld::TileSet const& tileSet) const
{
    SDL_Rect displayPos = m_displayPos;
    SDL_Rect finalSize = {0,0,0,0};
    Uint16 tileNumWidth = 0;
    Uint16 maxTileNumWidth = 0;
    Uint16 tileNumHeight = 0;

    for (std::vector<std::vector<Tile> >::const_iterator yit = tileSet.cbegin(); tileSet.cend() != yit; ++yit)
    {
        tileNumHeight++;

        for (std::vector<Tile>::const_iterator xit = yit->cbegin(); yit->cend() != xit; ++xit)
        {
            tileNumWidth++;

            SDL_BlitSurface(m_tiles[*xit], NULL, screen, &displayPos);
            displayPos.x += m_tileMask.w;
        }

        (tileNumWidth <= maxTileNumWidth) || (maxTileNumWidth = tileNumWidth);
        tileNumWidth = 0;

        displayPos.x = m_displayPos.x;
        displayPos.y += m_tileMask.h;
    }

    finalSize.w = maxTileNumWidth * m_tileMask.w;
    finalSize.h = tileNumHeight * m_tileMask.h;

    return finalSize;
}

SDL_Rect TileDisplayZone::render(SDL_Surface* screen, Position tilePos, Tile tile) const
{
    SDL_Rect displayPos = {tilePos.x * m_tileMask.w + m_displayPos.x, tilePos.y * m_tileMask.h + m_displayPos.y};
    SDL_BlitSurface(m_tiles[tile], NULL, screen, &displayPos);

    return displayPos;
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
