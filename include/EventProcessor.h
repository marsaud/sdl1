#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

#include <string>
#include <SDL/SDL.h>

class EventProcessor
{
    public:
        EventProcessor();
        virtual ~EventProcessor();
        std::string process(SDL_Event const& event) const;
    protected:
    private:
};

#endif // EVENTPROCESSOR_H
