#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

int** init_matrice(size_t height, size_t width);

void free_matrice(int** A, size_t height);

void max(int** A, size_t* x, size_t* y, size_t rhomax);

void line_trace(SDL_Surface* input, double theta, double rho);

void hough_trace(int** A, double x, double y, double rhomax);

void hough_transform(SDL_Surface* input);

#endif
