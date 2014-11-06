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

    MovementController movementController(&world);
    Position partyPos;

    ScreenZone* screenZoneRight = NULL;
    TextRollZone* textRollZone = NULL;
    ZoneDisplayZone* zoneDisplayZone = NULL;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "Unable to init SDL: " << std::endl << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "Unable to init SDL_ttf: " << std::endl << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16,
                              SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (NULL == screen )
    {
        std::cerr << "Unable to set video mode: " << std::endl << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    font = TTF_OpenFont("fonts/coure.fon", FONT_SIZE);
    if (NULL == font)
    {
        std::cerr << "Unable to load font: " << std::endl << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    screenZoneRight = new ScreenZone(TEXT_ZONE_RIGHT, TEXT_ZONE_TOP, font);
    textRollZone = new TextRollZone(TEXT_ZONE_LEFT, TEXT_ZONE_TOP, font);
    zoneDisplayZone = new ZoneDisplayZone(0,0);

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        while (SDL_PollEvent(&event))
        {
            // check for messages
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
            partyPos = movementController.handleEvent(event);


        } // end of message processing

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        textRollZone->render(screen, TextRollZone::REVERSE);
        zoneDisplayZone->render(screen, world);
        // debug fashion
        screenZoneRight->render(screen, patch::to_string(world.getPartyTile().x) + ":" + patch::to_string(world.getPartyTile().y));

        SDL_Flip(screen);
    } // end main loop

    delete textRollZone;
    delete screenZoneRight;
    TTF_CloseFont(font);
    SDL_FreeSurface(screen);

    TTF_Quit();
    SDL_Quit();

    std::cout << "Exited cleanly" << std::endl;
    return 0;
}
