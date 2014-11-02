#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef struct Position Position;
struct Position
{
    unsigned short int x;
    unsigned short int y;
};

enum Move
{
    MOVE_NOT, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT
};

enum Tile
{
    TILE_NONE, TILE_DIRT, TILE_FOREST, TILE_GRASS, TILE_HILL, TILE_MOUNT, TILE_WATER, TILE_LIST_SIZE
};

#endif // COMMON_H_INCLUDED
