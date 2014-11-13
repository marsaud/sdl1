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

Position operator+(Position const& pos, Movement const& mov);
bool operator==(Position const& posl, Position const& posr);

enum Move
{
    MOVE_NOT, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_LIST_SIZE
};

enum Action
{
    ACTION_NONE, ACTION_ENTER_ZONE, ACTION_LIST_SIZE
};

enum Tile
{
    TILE_NONE, TILE_CAVE, TILE_DIRT, TILE_FOREST, TILE_GRASS, TILE_HILL, TILE_MOUNT, TILE_WATER, TILE_PARTY, TILE_LIST_SIZE
};

#endif // COMMON_H_INCLUDED
