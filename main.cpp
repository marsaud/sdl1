#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "main.h"

#include <iostream>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "common.h"
#include "init.h"
#include "Logger.h"
#include "MessageProcessor.h"
#include "DynamicWorld.h"
#include "MovementController.h"
#include "ScreenZone.h"
#include "TextRollZone.h"
#include "ZoneDisplayZone.h"

namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}

int main ( int argc, char** argv )
{
    DynamicWorld world;

    SDL_Surface* screen = NULL;
    TTF_Font* font = NULL;
    SDL_Event event;

    Logger log;
    MessageProcessor messageProcessor;

    std::string display = "";

    MovementController movementController;
    Move move = MOVE_NOT;

    ScreenZone* screenZoneRight = NULL;
    TextRollZone* textRollZone = NULL;
    ZoneDisplayZone* zoneDisplayZone = NULL;

    if (1 == initVideo(SCREEN_WIDTH, SCREEN_HEIGHT, "fonts/coure.fon", FONT_SIZE, screen, font))
    {
        return 1;
    }

    screenZoneRight = new ScreenZone(TEXT_ZONE_RIGHT, TEXT_ZONE_TOP, font);
    textRollZone = new TextRollZone(TEXT_ZONE_LEFT, TEXT_ZONE_TOP, font);
    zoneDisplayZone = new ZoneDisplayZone(0,0);

    // program main loop
    bool done = false;
    while (!done)
    {
        // event processing loop
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = true;
                    break;
                default:
                    break;
                }

                break;
            }

            if (messageProcessor.process(event, log))
            {
                textRollZone->clear();
                log.rewind();
                for (unsigned int idx = 0; idx < TextRollZone::BUFFER_SIZE; idx++)
                {
                    if (!log.pop(display))
                        break;
                    else
                        textRollZone->push(display);
                }
            }

            move = movementController.handleEvent(event);
            world.move(move);

        } // end of event processing

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        textRollZone->render(screen, TextRollZone::REVERSE);
        zoneDisplayZone->render(screen, world);

        // debug fashion
        screenZoneRight->render(screen, patch::to_string(world.getPartyTile().x) + ":" + patch::to_string(world.getPartyTile().y));

        SDL_Flip(screen);

        SDL_Delay(40);
    } // end main loop

    delete textRollZone;
    delete screenZoneRight;

    shutdownVideo(screen, font);

    std::cout << "Exited cleanly" << std::endl;
    return EXIT_SUCCESS;
}
