#include "MessageProcessor.h"

MessageProcessor::MessageProcessor()
{
    //ctor
}

MessageProcessor::~MessageProcessor()
{
    //dtor
}

bool MessageProcessor::process(SDL_Event const& event, Logger & log) const
{
    std::string message = "";
    switch (event.type)
    {
    case SDL_QUIT:
        message = "Quit";
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            message = "Quit";
            break;
        case SDLK_UP:
            message = "Up";
            break;
        case SDLK_DOWN:
            message = "Down";
            break;
        case SDLK_LEFT:
            message = "Left";
            break;
        case SDLK_RIGHT:
            message = "Right";
            break;
        default:
            message = "?";
            break;
        }
        break;

    default:
        break;
    }

    if ("" != message)
    {
        log.push(message);
        return true;
    }
    else
    {
        return false;
    }

}
