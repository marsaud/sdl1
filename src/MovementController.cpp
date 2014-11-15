#include "MovementController.h"

MovementController::MovementController()
{
    //ctor
}

MovementController::~MovementController()
{
    //dtor
}

Move MovementController::handleEvent(SDL_Event const& event) const
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

    return move;
}

void MovementController::handleEvent(SDL_Event const& event, Move & move, int & playerKey) const
{
    move = MOVE_NOT;
    playerKey = 0;

    if (SDL_KEYDOWN == event.type)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP :
        case SDLK_z:
        case SDLK_o:
            move = MOVE_UP;
            break;
        case SDLK_DOWN :
        case SDLK_s:
        case SDLK_l:
            move = MOVE_DOWN;
            break;
        case SDLK_LEFT :
        case SDLK_q:
        case SDLK_k:
            move = MOVE_LEFT;
            break;
        case SDLK_RIGHT :
        case SDLK_d:
        case SDLK_m:
            move = MOVE_RIGHT;
            break;
        default :
            break;
        }

        switch (event.key.keysym.sym)
        {
        case SDLK_UP :
        case SDLK_DOWN :
        case SDLK_LEFT :
        case SDLK_RIGHT :
            playerKey = 1;
            break;
        case SDLK_z:
        case SDLK_s:
        case SDLK_q:
        case SDLK_d:
            playerKey = 2;
            break;
        case SDLK_o:
        case SDLK_l:
        case SDLK_k:
        case SDLK_m:
            playerKey = 3;
            break;
        default:
            break;
        }
    }
}
