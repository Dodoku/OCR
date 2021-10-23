#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

int** init_matrice(size_t height, size_t width);

void free_matrice(int** A, size_t height);

void print_matrice(int**A, size_t height, size_t width);

SDL_Surface* better_print(int** A, size_t height, size_t width);

void place_point(int** A, size_t x, size_t y, int max);

void mapping(SDL_Surface* image, int** A, int mid);

void hough_transform();

SDL_Surface* function_print();

#endif
