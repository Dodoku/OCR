#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "image.h"

//return an empty SDL_Surface
SDL_Surface* create_empty(int w, int h){
    SDL_Surface* ret = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            set_pixel(ret,i,j,to_color(255,255,255,255));
        }
    }
    return ret;
}

//return the surface from a path to load a picture
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

//return the pixel at (x,y) as a SDL_color 
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

//return a SDL_Color from a Uint32
SDL_Color int_to_color(Uint32 value){
    SDL_Color color;
    color.r = value & 0xFF;
    color.g = (value >> 8) & 0xFF;
    color.b = (value >> 16) & 0xFF;
    color.a = value >> 24;
    return color;
}

//return a Uint32 from a SDL_color
Uint32 color_to_int(SDL_Color color){
    return (Uint32)((color.r) 
            + (color.g << 8) 
            + (color.b << 16) 
            + (color.a << 24));
}
