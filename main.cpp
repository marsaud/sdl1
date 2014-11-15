#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <string>
#include <sstream>
#include <unordered_map>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "main.h"
#include "common.h"
#include "init.h"

#include "StaticWorld.h"
#include "PartyPlayer.h"

#include "Logger.h"
#include "MessageProcessor.h"
#include "MovementController.h"
#include "ActionController.h"

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

    std::unordered_map<int, PartyPlayer*> players;

    /** @todo temporary begin */
    PartyPlayer* pl = new PartyPlayer(world);
    players[pl->getKey()] = pl;
    pl =  new PartyPlayer(world);
    players[pl->getKey()] = pl;
    pl =  new PartyPlayer(world);
    players[pl->getKey()] = pl;

    int playerMoveKey = 0;
    int playerActionKey =0;

    SDL_Rect offset;
    /** @todo temporary end */

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

            movementController.handleEvent(event, move, playerMoveKey);
            actionController.handleEvent(event, action, playerActionKey);

            if (0 != playerActionKey)
                players[playerActionKey]->process(action);
            if (0 != playerMoveKey)
                players[playerMoveKey]->move(move);

        } // end of event processing

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        textRollZone->render(screen, TextRollZone::REVERSE);

        offset = {0,0,0,0};
        zoneDisplayZone->render(screen, world->getArea(players[1]->getArea()), players, offset);
        offset.x += 420;
        zoneDisplayZone->render(screen, world->getArea(players[2]->getArea()), players, offset);
        offset.x += 420;
        zoneDisplayZone->render(screen, world->getArea(players[3]->getArea()), players, offset);

        SDL_Flip(screen);

        currentTime = SDL_GetTicks();
        ellapsedTime = currentTime - referenceTime;
        if(ellapsedTime < FRAME_LENGTH)
        {
            SDL_Delay(FRAME_LENGTH - ellapsedTime);
        }
    } // end main loop



    for (std::unordered_map<int, PartyPlayer*>::iterator it = players.begin(); players.end() != it; ++it)
    {
        delete it->second;
    }
    players.clear();

    delete textRollZone;
    delete zoneDisplayZone;
    delete world;

    TileDisplayZone::free();
    PartyPlayer::free();

    quitVideo(screen, font);

    return EXIT_SUCCESS;
}
