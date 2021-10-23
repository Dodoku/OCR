#ifndef BLACK_H
#define BLACK_H

#include <SDL2/SDL.h>

SDL_Surface *to_grayscale(SDL_Surface *image);

SDL_Color grayscale(SDL_Color color);

void otsu_transform(SDL_Surface* image);

int otsu_threshold(int* A, int N);

void otsu_histogram(SDL_Surface* image, int* A);

SDL_Surface* otsu(SDL_Surface* input);

#endif
