#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "common.h"
#include "EventProcessor.h"
#include "DynamicWorld.h"
#include "MovementController.h"
#include "ScreenZone.h"
#include "TextRollZone.h"
#include "TileDisplayZone.h"

#define SCREEN_HEIGHT   720
#define SCREEN_WIDTH    1280

#define TEXT_ZONE_TOP   576
#define TEXT_ZONE_LEFT  20
#define TEXT_ZONE_RIGHT 660

#define FONT_SIZE       22

using namespace std;

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
    SDL_Surface* screen = NULL;
    TTF_Font* font = NULL;
    SDL_Event event;
    EventProcessor processor;
    string display = "Start";

    DynamicWorld world;

    MovementController movementController(&world);
    Position partyPos;

    ScreenZone* screenZoneRight = NULL;
    TextRollZone* textRollZone = NULL;
    TileDisplayZone* tileDisplayZone = NULL;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cerr << "Unable to init SDL: " << endl << SDL_GetError() << endl;
        return 1;
    }

    if (TTF_Init() == -1)
    {
        cerr << "Unable to init SDL_ttf: " << endl << TTF_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16,
                              SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (NULL == screen )
    {
        cerr << "Unable to set video mode: " << endl << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    font = TTF_OpenFont("fonts/coure.fon", FONT_SIZE);
    if (NULL == font)
    {
        cerr << "Unable to load font: " << endl << TTF_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    screenZoneRight = new ScreenZone(TEXT_ZONE_RIGHT, TEXT_ZONE_TOP, font);
    textRollZone = new TextRollZone(TEXT_ZONE_LEFT, TEXT_ZONE_TOP, font);
    textRollZone->push(display);
    tileDisplayZone = new TileDisplayZone(0,0);

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

            display = processor.process(event);
            if ("" != display)
                textRollZone->push(display);
            partyPos = movementController.handleEvent(event);


        } // end of message processing

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        textRollZone->render(screen);
        tileDisplayZone->render(world, screen);
        // debug fashion
        screenZoneRight->render(patch::to_string(partyPos.x) + ":" + patch::to_string(partyPos.y),screen);


        SDL_Flip(screen);
    } // end main loop

    delete tileDisplayZone;
    delete textRollZone;
    delete screenZoneRight;
    TTF_CloseFont(font);
    SDL_FreeSurface(screen);

    TTF_Quit();
    SDL_Quit();

    cout << "Exited cleanly" << endl;
    return 0;
}
