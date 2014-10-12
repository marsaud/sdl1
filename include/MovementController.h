#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H

#include <SDL/SDL.h>

#include "common.h"
#include "DynamicWorld.h"

class MovementController
{
    public:
        MovementController(DynamicWorld* world);
        virtual ~MovementController();
        Position handleEvent(SDL_Event event) const;
    protected:
    private:
        DynamicWorld* m_dynamicWorld;
};

#endif // MOVEMENTCONTROLLER_H
