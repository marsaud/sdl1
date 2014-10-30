#include "MovementController.h"

MovementController::MovementController(DynamicWorld* const world)
{
    m_dynamicWorld = world;
}

MovementController::~MovementController()
{
    //dtor
}

Position MovementController::handleEvent(SDL_Event const event) const
{
    Move move = MOVE_NOT;
    if (SDL_KEYDOWN == event.type)
    {

        switch (event.key.keysym.sym)
        {
        case SDLK_UP :
            move = MOVE_UP;
            break;
        case SDLK_DOWN :
            move = MOVE_DOWN;
            break;
        case SDLK_LEFT :
            move = MOVE_LEFT;
            break;
        case SDLK_RIGHT :
            move = MOVE_RIGHT;
            break;
        default :
            break;
        }
    }

    return m_dynamicWorld->move(move);
}
