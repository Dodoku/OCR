#ifndef BLACK_H
#define BLACK_H

#include <SDL2/SDL.h>

SDL_Surface *to_greyscale(SDL_Surface *image);

SDL_Surface *to_black_and_white(SDL_Surface *image);

SDL_Color greyscale(SDL_Color color);

SDL_Color black_and_white(Uint32 value, Uint32 average);

Uint32 get_average(SDL_Surface *image);

#endif