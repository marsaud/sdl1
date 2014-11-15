#include "ActionController.h"

ActionController::ActionController()
{
    //ctor
}

ActionController::~ActionController()
{
    //dtor
}

Action ActionController::handleEvent(SDL_Event const& event) const
{
    Action action = ACTION_NONE;

    if (SDL_KEYDOWN == event.type)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_e:
            action = ACTION_ENTER_ZONE;
            break;
        default:
            break;
        }
    }

    return action;
}

void ActionController::handleEvent(SDL_Event const& event, Action & action, int & playerKey) const
{
    action = ACTION_NONE;
    playerKey = 0;

    if (SDL_KEYDOWN == event.type)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_e:
        case SDLK_p:
        case SDLK_SPACE:
            action = ACTION_ENTER_ZONE;
            break;
        default:
            break;
        }

        switch (event.key.keysym.sym)
        {
        case SDLK_e:
            playerKey = 2;
            break;
        case SDLK_p:
            playerKey = 3;
            break;
        case SDLK_SPACE:
            playerKey = 1;
            break;
        default:
            break;
        }
    }
}
