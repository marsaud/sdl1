#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <string>
#include <SDL/SDL.h>

#include "Logger.h"

class MessageProcessor
{
public:
    MessageProcessor();
    virtual ~MessageProcessor();

    bool process(SDL_Event const& event, Logger & log) const;
protected:
private:
};

#endif // MESSAGEPROCESSOR_H
