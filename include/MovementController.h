#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H

#include <SDL/SDL.h>

#include "common.h"
#include "DynamicWorld.h"

class MovementController
{
public:
    MovementController();
    virtual ~MovementController();

    Move handleEvent(SDL_Event const& event) const;
protected:
private:
};

#endif // MOVEMENTCONTROLLER_H
