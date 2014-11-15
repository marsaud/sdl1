#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <SDL/SDL.h>

#include "common.h"

class ActionController
{
public:
    ActionController();
    virtual ~ActionController();

    Action handleEvent(SDL_Event const& event) const;
    void handleEvent(SDL_Event const& event, Action & action, int & playerKey) const;
protected:
private:
};

#endif // ACTIONCONTROLLER_H
