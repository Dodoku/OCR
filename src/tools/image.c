#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "image.h"

/*
 * return a empty surface
 * @param w,h (int) : the heigh and the width of the surface
 * @return (SDL_Surface*) : the empty surface
 * @author Nicolas Prevost
 */
SDL_Surface *create_empty(int w, int h) {
    SDL_Surface *ret = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            set_pixel(ret, i, j, to_color(255, 255, 255, 255));
        }
    }
    return ret;
}

/*
 * try to load a picture from the path
 * @param path (char*) : the path of the picture
 * @return (SDL_Surface*) : the loaded surface
 * @author Valentin Uhlrich
 */
SDL_Surface *load(char *path) {
    SDL_Surface *image = IMG_Load(path);
    if (!image) {
        errx(1, "%s\n", IMG_GetError());
    }
    return image;
}

/*
 * save the picture at the given path
 * @param (SDL_Surface*) : the picture to save
 * @param path (char*) : the path were to save
 * @author Valentin Uhlrich
 */
void save(SDL_Surface *image, char *path) {
    if (IMG_SaveJPG(image, path, 100) < 0) {
        errx(1, "%s\n", IMG_GetError());
    }
}

// return the pixel at (x,y) as a SDL_color
SDL_Color get_pixel(SDL_Surface *image, int x, int y) {
    Uint32 *pixel
      = (Uint32 *) ((Uint8 *) image->pixels + x * image->format->BytesPerPixel
                    + y * image->pitch);
    return int_to_color(*pixel);
}

void set_pixel(SDL_Surface *image, int x, int y, SDL_Color color) {
    Uint32 *pixel
      = (Uint32 *) ((Uint8 *) image->pixels + x * image->format->BytesPerPixel
                    + y * image->pitch);
    *pixel = color_to_int(color);
}

SDL_Color to_color(int r, int g, int b, int a) {
    return (SDL_Color){r, g, b, a};
}

// return a SDL_Color from a Uint32
SDL_Color int_to_color(Uint32 value) {
    SDL_Color color;
    color.r = value & 0xFF;
    color.g = (value >> 8) & 0xFF;
    color.b = (value >> 16) & 0xFF;
    color.a = value >> 24;
    return color;
}

// return a Uint32 from a SDL_color
Uint32 color_to_int(SDL_Color color) {
    return (Uint32) ((color.r) + (color.g << 8) + (color.b << 16)
                     + (color.a << 24));
}

/*
 * rescale the picture
 * @param image (SDL_Surface*) : the picture to rescale
 * @param w,h (int) : the new sclale of the picure
 * @return (SDL_Surface*) : return the scale picure
 * @author Nicolas Prevost
 */
SDL_Surface* resize(SDL_Surface* image, int w, int h)
{
    SDL_Surface* ret = create_empty(w, h);
    for(int i=0;i<image->w;i++)
    {
        for(int j=0;j<image->h;j++)
        {
            set_pixel(ret,
                (double)i/(double)(image->w)*(double)w,
                (double)j/(double)(image->h)*(double)h,
                get_pixel(image,i,j));
        }
    }
    return ret;
}
