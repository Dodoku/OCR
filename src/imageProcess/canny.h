#ifndef CANNY
#define CANNY

#include <SDL2/SDL.h>

void gfilter(double** filter, size_t row, size_t column, double sigma);

SDL_Surface* gaussian(SDL_Surface* input);

SDL_Color isedge(SDL_Surface* input, size_t x, size_t y);

SDL_Surface* edgemap(SDL_Surface* input);

#endif