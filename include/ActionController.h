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
protected:
private:
};

#endif // ACTIONCONTROLLER_H
