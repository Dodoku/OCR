#include <stdio.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"

SDL_Color greyscale(SDL_Color color) {
    SDL_Color grey;
    Uint32 value = (color.r + color.g + color.b)/3;
    grey.r = value;
    grey.g = value;
    grey.b = value;
    grey.a = color.a;
    return grey;
}

SDL_Color black_and_white(Uint32 value, Uint32 average) {
    SDL_Color color;
    color.a = 255;
    if (value < average) {
        color.r = 0;
        color.g = 0;
        color.b = 0;
        return color;
    }
    color.r = 255;
    color.g = 255;
    color.b = 255;
    return color;
}

Uint32 get_average(SDL_Surface *image) {
    Uint32 average = 0;
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            SDL_Color color = get_pixel(image, i, j);
            color = greyscale(color);
            average += color.r;
        }
    }
    Uint32 temp = (average / (image->w * image->h)); 
    return temp;
}

SDL_Surface *to_greyscale(SDL_Surface *image) {
    SDL_Surface *result = create_empty(image->w, image->h);
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            SDL_Color color = get_pixel(image, i, j);
            color = greyscale(color);
            set_pixel(result, i, j, color);
        }
    }
    return result;
}

SDL_Surface *to_black_and_white(SDL_Surface *image) {
    SDL_Surface *result = create_empty(image->w, image->h);
    Uint32 average = get_average(image);
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            Uint32 value = get_pixel(image, i, j).r;
            SDL_Color color = black_and_white(value, average);
            set_pixel(result, i, j, color);
        }
    }
    return result;
}
