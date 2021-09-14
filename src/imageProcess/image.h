#ifndef IMAGE_DEF
#define IMAGE_DEF

#include <SDL2/SDL.h>

SDL_Surface* load(char* path);

SDL_Color get_pixel(SDL_Surface* image, int x, int y);
void set_pixel(SDL_Surface* image, int x, int y, SDL_Color color);

SDL_Color int_to_color(Uint32 num);
Uint32 color_to_int(SDL_Color color);

#endif
