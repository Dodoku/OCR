#ifndef DIGIT_PICTURE_DEF
#define DIGIT_PICTURE_DEF
#include <SDL2/SDL_image.h>

void display_digit(SDL_Surface *image, int x, int y, int n, SDL_Color color);

SDL_Surface* generate_digit_picture(char* sudoku, char* solved);

#endif
