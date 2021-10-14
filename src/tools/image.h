#ifndef IMAGE_DEF
#define IMAGE_DEF

#include <SDL2/SDL.h>

SDL_Surface *create_empty(int w, int h);

SDL_Surface *load(char *path);
void save(SDL_Surface *image, char *path);

SDL_Color get_pixel(SDL_Surface *image, int x, int y);
void set_pixel(SDL_Surface *image, int x, int y, SDL_Color color);

SDL_Color to_color(int r, int g, int b, int a);
SDL_Color int_to_color(Uint32 num);
Uint32 color_to_int(SDL_Color color);

SDL_Surface *resize_image(SDL_Surface* surface, SDL_Rect position);

#endif
