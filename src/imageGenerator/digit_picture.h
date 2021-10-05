#ifndef DIGIT_PICTURE_DEF
#define DIGIT_PICTURE_DEF
#include <SDL2/SDL_image.h>

void display_digit(SDL_Surface *image, int x, int y, int n);

void generate_digit_picture(int sudoku[], char *path[]);

#endif
