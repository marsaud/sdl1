#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <iostream>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

int initVideo(int screenWidth, int screenHeight, std::string const& fontPath, int fontSize, SDL_Surface* & screen, TTF_Font* & font);

void quitVideo(SDL_Surface* screen, TTF_Font* font);

#endif // INIT_H_INCLUDED


