#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef struct Position Position;
typedef struct Position Movement;
struct Position
{
    signed short x;
    signed short y;

    Position& operator+=(Movement const& mov);
};

enum Move
{
    MOVE_NOT, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_LIST_SIZE
};

enum Tile
{
    TILE_NONE, TILE_DIRT, TILE_FOREST, TILE_GRASS, TILE_HILL, TILE_MOUNT, TILE_WATER, TILE_LIST_SIZE
};

Position operator+(Position const& pos, Movement const& mov);


#endif // COMMON_H_INCLUDED
