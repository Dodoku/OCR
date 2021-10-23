#ifndef BLACK_H
#define BLACK_H

#include <SDL2/SDL.h>

SDL_Surface *to_greyscale(SDL_Surface *image);

SDL_Surface *to_black_and_white(SDL_Surface *image);

SDL_Color greyscale(SDL_Color color);

SDL_Color black_and_white(Uint32 value, Uint32 average);

Uint32 get_average(SDL_Surface *image);

void otsu_transform(SDL_Surface* image);

int otsu_threshold(int* A, int N);

void otsu_histogram(SDL_Surface* image, int* A);

SDL_Surface* otsu(SDL_Surface* input);

#endif
