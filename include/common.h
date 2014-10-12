#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef struct Position Position;
struct Position
{
    int x;
    int y;
};

enum Move
{
    MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_NOT
};

enum Tile
{
    TILE_DIRT, TILE_GRASS, TILE_FOREST, TILE_HILL, TILE_MOUNT, TILE_WATER
};

#endif // COMMON_H_INCLUDED
