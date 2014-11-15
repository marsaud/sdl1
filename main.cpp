#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "main.h"
#include "common.h"
#include "init.h"
#include "Logger.h"
#include "MessageProcessor.h"
#include "DynamicWorld.h"

#include "PartyPlayer.h"

#include "MovementController.h"
#include "ActionController.h"
#include "ScreenZone.h"
#include "TextRollZone.h"
#include "ZoneDisplayZone.h"
#include "PartyPlayer.h"

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
    SDL_Surface *screen = NULL;
    TTF_Font *font = NULL;

    if (1 == initVideo(SCREEN_WIDTH, SCREEN_HEIGHT, "fonts/coure.fon", FONT_SIZE, screen, font))
    {
        return 1;
    }

    TileDisplayZone::init();
    PartyPlayer::init();

    SDL_Event event;
    Logger log;
    MessageProcessor messageProcessor;

    std::string display = "";

    MovementController movementController;
    ActionController actionController;

    Move move = MOVE_NOT;
    Action action = ACTION_NONE;

    TextRollZone *textRollZone = new TextRollZone(TEXT_ZONE_LEFT, TEXT_ZONE_TOP, font);
    ZoneDisplayZone *zoneDisplayZone = new ZoneDisplayZone(0,0);

    Uint32 referenceTime;
    Uint32 currentTime;
    Uint32 ellapsedTime;

    StaticWorld *world = new StaticWorld("scenario1", "data");
    PartyPlayer *player = new PartyPlayer(world);

    // program main loop
    bool done = false;
    while (!done)
    {
        referenceTime = SDL_GetTicks();

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
            action = actionController.handleEvent(event);

            player->process(action);
            player->move(move);

        } // end of event processing

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        textRollZone->render(screen, TextRollZone::REVERSE);
        zoneDisplayZone->render(screen, world->getArea(player->getArea()), player);

        SDL_Flip(screen);

        currentTime = SDL_GetTicks();
        ellapsedTime = currentTime - referenceTime;
        if(ellapsedTime < FRAME_LENGTH)
        {
            SDL_Delay(FRAME_LENGTH - ellapsedTime);
        }
    } // end main loop

    TileDisplayZone::free();
    PartyPlayer::free();

    delete textRollZone;
    delete zoneDisplayZone;
    delete world;
    delete player;

    quitVideo(screen, font);

    return EXIT_SUCCESS;
}
