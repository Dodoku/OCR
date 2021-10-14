#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

int** init_matrice(int height, int width);

void print_matrice(int**A, size_t height, size_t width);

void free_matrice(int** A, size_t height);

#endif
