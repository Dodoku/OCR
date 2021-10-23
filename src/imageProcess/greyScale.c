#include <stdio.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"

SDL_Color greyscale(SDL_Color color) {
    SDL_Color grey;
    Uint32 value = (color.r + color.g + color.b)/3;
    grey.r, grey.g, grey.b = value;
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

Uint32 get_average(SDL_Surface *image){
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

SDL_Surface* to_greyscale(SDL_Surface* image){
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

SDL_Surface* to_black_and_white(SDL_Surface *image) {
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

void otsu_histogram(SDL_Surface* image, int* A){
    size_t height = image->h, width = image->w;
    for(){
        for(){
            SDL_Color color = get_pixel(image, i, j);
            A[color.r] += 1;
        }
    }
}

int otsu_threshold(int* A){
    int threshold = 0, var_max = 0, sum = 0, sumB = 0;
    int q1 = 0, q2 = 0, u1 = 0, u2 = 0, u, o;
    for(size_t i = 0; i <= 255; i++)
        sum += i * A[i];
    for(size_t t = 0; t <= 255; t++){
        q1 += A[t];
        if (q == 0)
            continue
        q2 = height * width - q1;
        sumB += t*A[t];
        u1 = sumB/q1;
        u2 = (sum - sumB)/q2;
        u = u1-u2;
        o = q1*q2*u*u;
        if(o > var_max){
            threshold = t;
            var_max = o;
        }
    }
    return threshold;
}

void otsu_transform(SDL_Surface* image){
    const SDL_Color black, white;
    black.a = white.a = white.r = white.g = white.b = 255;
    black.r = black.g = black.b = ;

    size_t height = image->h, width = image->w;
    int A[256];
    for(size_t i = 0; i < 256; i++)
        A[i] = 0;
    
    otsu_histogram(image, A);
    int threshold = otsu_threshold(A);
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            if(get_pixel(image, i, j).r > threshold)
                set_pixel(image, i, j, black);
            else
                set_pixel(image, i, j, white);
        }
    }
}

sDL_Surface* otsu(SDL_Surface* input){
    SDL_Surface* output= to_greyscale(input);
    otsu_transform(output);
    return output;
}
