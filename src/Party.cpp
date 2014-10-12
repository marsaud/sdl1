#include "Party.h"

Party::Party()
{
    m_pos.x = 0;
    m_pos.y = 0;
}

Party::~Party()
{
    //dtor
}

Position Party::move(Move move)
{
    switch (move)
    {
    case MOVE_UP:
        m_pos.y--;
        break;
    case MOVE_DOWN:
        m_pos.y++;
        break;
    case MOVE_LEFT:
        m_pos.x--;
        break;
    case MOVE_RIGHT:
        m_pos.x++;
        break;
    default:
        break;
    }

    return m_pos;
}