#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef struct Position Position;
struct Position
{
    unsigned int x;
    unsigned int y;
};

enum Move
{
    MOVE_NOT, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT
};

#define TILE_LIST_SIZE  7
enum Tile
{
    TILE_NONE, TILE_DIRT, TILE_GRASS, TILE_FOREST, TILE_HILL, TILE_MOUNT, TILE_WATER
};

#endif // COMMON_H_INCLUDED
