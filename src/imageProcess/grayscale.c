#include <stdio.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"

SDL_Color grayscale(SDL_Color color) {
    Uint32 value = (color.r + color.g + color.b)/3;
    return to_color(value, value, value, color.a);
}

/**
 * @brief Convert an image to grayscale
 * /!\ IMAGE IS DESTROYED /!\
 * @param image (SDL_Surface*) The image to convert
 * @return SDL_Surface* grayscale image
 * @author Nicolas Prevost
 */
SDL_Surface* to_grayscale(SDL_Surface* image){
    SDL_Surface *result = create_empty(image->w, image->h);
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            SDL_Color color = get_pixel(image, i, j);
            color = grayscale(color);
            set_pixel(result, i, j, color);
        }
    }
    SDL_FreeSurface(image);
    return result;
}

void otsu_histogram(SDL_Surface* image, int* A){
    size_t height = image->h, width = image->w;
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            SDL_Color color = get_pixel(image, i, j);
            A[color.r] += 1;
        }
    }
}

int otsu_threshold(int* A, int N){
    double threshold = 0, var_max = 0, sum = 0, sumB = 0;
    double q1 = 0, q2 = 0, u1 = 0, u2 = 0, u, o;
    for(size_t i = 0; i <= 255; i++)
        sum += i * A[i];
    for(size_t t = 0; t <= 255; t++){
        q1 += A[t];
        if (q1 == 0)
            continue;
        q2 = N - q1;
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
    return (int) threshold;
}

void otsu_transform(SDL_Surface* image){
    const SDL_Color black = to_color(0,0,0,255);
    const SDL_Color white = to_color(255,255,255,255);

    size_t height = image->h, width = image->w;
    int A[256];
    for(size_t i = 0; i < 256; i++)
        A[i] = 0;
    
    otsu_histogram(image, A);

    int threshold = otsu_threshold(A, height*width);
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            if(get_pixel(image, i, j).r > threshold)
                set_pixel(image, i, j, black);
            else
                set_pixel(image, i, j, white);
        }
    }
}

SDL_Surface* otsu(SDL_Surface* input){
    SDL_Surface* output = to_grayscale(input);
    otsu_transform(output);
    return output;
}
