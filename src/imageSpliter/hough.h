#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

int** init_matrice(size_t height, size_t width);

void free_matrice(int** A, size_t height);

int max(int** A, size_t rhomax);

void hough_lines(SDL_Surface* input, size_t A, size_t rhomax, size_t threshold);

void line_trace(SDL_Surface* input, double theta, double rho, double rhomax);

void hough_trace(int** A, double x, double y, double rhomax);

SDL_Surface* hough_transform(SDL_Surface* input);

#endif
