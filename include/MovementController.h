#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H

#include <SDL/SDL.h>

#include "common.h"

class MovementController
{
public:
    MovementController();
    virtual ~MovementController();

    Move handleEvent(SDL_Event const& event) const;
    void handleEvent(SDL_Event const& event, Move & move, int & playerKey) const;
protected:
private:
};

#endif // MOVEMENTCONTROLLER_H
