#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

int** init_matrice(size_t height, size_t width);

void print_matrice(int**A, size_t height, size_t width);

SDL_Surface* better_print(int** A, size_t height, size_t width);

void mapping(SDL_Surface* image, int** A, int mid);

void place_point(int** A, size_t x, size_t y, int max);

void hough_transform(SDL_Surface* image);

void free_matrice(int** A, size_t height);

#endif
