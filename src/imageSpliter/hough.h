#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

int** init_matrice(size_t height, size_t width);

void free_matrice(int** A, size_t height);

void place_point(int** A, size_t x, size_t y, int max);

void mapping(SDL_Surface* image, int** A, int mid);

void hough_transform();

void hough_trace(SDL_Surface* output, double x, double y, double rhomax);

SDL_Surface* hough_mapping(SDL_Surface* input);

SDL_Surface* function_print();

#endif
