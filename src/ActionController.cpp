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
