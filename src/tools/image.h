#ifndef IMAGE_DEF
#define IMAGE_DEF

#include <SDL2/SDL.h>

struct pic_pos
{
    SDL_Surface* image;
    int x1;
    int y1;
    int x2;
    int y2;
};

SDL_Surface *create_empty(int w, int h);
SDL_Surface *copy(SDL_Surface* src);

SDL_Surface *load(char *path);
void save(SDL_Surface *image, char *path);

SDL_Color get_pixel(SDL_Surface *image, int x, int y);
void set_pixel(SDL_Surface *image, int x, int y, SDL_Color color);

SDL_Color to_color(int r, int g, int b, int a);
SDL_Color int_to_color(Uint32 num);
Uint32 color_to_int(SDL_Color color);

SDL_Surface* resize(SDL_Surface* image, int w, int h);

#endif
