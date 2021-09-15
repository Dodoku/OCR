#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "image.h"

SDL_Surface* load(char* path){
    SDL_Surface *image = IMG_Load(path);
    if(!image){
        errx(1, "%s\n", IMG_GetError());
    }
    return image;
}

void save(SDL_Surface* image, char* path){
    if(IMG_SaveJPG(image, path, 100) < 0){
        errx(1, "%s\n", IMG_GetError());
    }
}

SDL_Color get_pixel(SDL_Surface* image, int x, int y){
    Uint32* pixel = (Uint32*) ((Uint8*) image->pixels 
                                    + x * image->format->BytesPerPixel
                                    + y * image->pitch);
    return int_to_color(*pixel);
}

void set_pixel(SDL_Surface* image, int x, int y, SDL_Color color){
    Uint32* pixel = (Uint32*) ((Uint8*) image->pixels 
                                    + x * image->format->BytesPerPixel
                                    + y * image->pitch);
    *pixel = color_to_int(color);  
}

SDL_Color to_color(int r, int g, int b, int a){
    return (SDL_Color) {r, g, b, a};
}

SDL_Color int_to_color(Uint32 value){
    SDL_Color color;
    color.r = value & 0xFF;
    color.g = (value >> 8) & 0xFF;
    color.b = (value >> 16) & 0xFF;
    color.a = value >> 24;
    return color;
}

Uint32 color_to_int(SDL_Color color){
    return (Uint32)((color.r) 
            + (color.g << 8) 
            + (color.b << 16) 
            + (color.a << 24));
}
