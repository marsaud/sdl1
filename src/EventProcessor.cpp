#include "EventProcessor.h"

using namespace std;

EventProcessor::EventProcessor()
{

}

EventProcessor::~EventProcessor()
{
    //dtor
}

string EventProcessor::process(SDL_Event const& event) const
{
    string display;

    switch (event.type)
    {
    case SDL_QUIT:
        display = "Quit";
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            display = "Quit";
            break;
        case SDLK_UP:
            display = "Up";
            break;
        case SDLK_DOWN:
            display = "Down";
            break;
        case SDLK_LEFT:
            display = "Left";
            break;
        case SDLK_RIGHT:
            display = "Right";
            break;
        default:
            display = "?";
            break;
        }
        break;

    default:
        display = "";
        break;
    }

    return display;
}
