#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

int** init_matrice(size_t height, size_t width);

void free_matrice(int** A, size_t height);

int max(int** A, size_t rhomax);

SDL_Surface* hough_print(int**A, size_t rhomax);

void line_trace(SDL_Surface* input, double theta, double rho, double rhomax);

void hough_trace(int** A, double x, double y, double rhomax);

SDL_Surface* hough_transform(SDL_Surface* input);

#endif
