#ifndef PARTY_H
#define PARTY_H

#include "common.h"

class Party
{
public:
    Party();
    virtual ~Party();

    Position getPosition() const;
    Position move(Move const move);
protected:
private:
    Position m_pos;
};

#endif // PARTY_H
