#include "common.h"

Position operator+(Position const& pos, Movement const& mov)
{
    Position sum;

    sum.x = pos.x + mov.x;
    sum.y = pos.y + mov.y;

    return sum;
}

Position& Position::operator+=(Movement const& mov)
{
    x += mov.x;
    y += mov.y;

    return *this;
}
