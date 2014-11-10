#include "init.h"

int initVideo(int screenWidth, int screenHeight, std::string const& fontPath, int fontSize, SDL_Surface* & screen, TTF_Font* & font)
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "Unable to init SDL: " << std::endl << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "Unable to init SDL_ttf: " << std::endl << TTF_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    screen = SDL_SetVideoMode(screenWidth, screenHeight, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if (NULL == screen )
    {
        std::cerr << "Unable to set video mode: " << std::endl << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    if (NULL == font)
    {
        std::cerr << "Unable to load font: " << std::endl << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    return 0;
}

void quitVideo(SDL_Surface* screen, TTF_Font* font)
{
    TTF_CloseFont(font);
    SDL_FreeSurface(screen);

    TTF_Quit();
    SDL_Quit();
}
