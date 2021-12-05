#include <stdio.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"

int filter[5][5] =
    {{ 1, 4, 6, 4, 1},
     { 4,16,24,16, 4},
     { 6,24,36,24, 6},
     { 4,16,24,16, 4},
     { 1, 4, 6, 4, 1}};

/**
 * Returne a new picture with a gaussian blur
 * /!\ IMAGE IS DESTROYED /!\
 * @param image (SDL_Image) : the picture on wich we apply the filter
 * @param n (int) : the times we apply the filter, to get a bigger effect
 * @return (SDL_Surface) : return the treated picture
 * @author Prevost Nicolas
 */

SDL_Surface* gaussian_blur(SDL_Surface* image, int n){
    SDL_Surface* new_image = create_empty(image->w, image->h);
    for(int o=0;o<n;o++){
        for(int i=2;i<image->w-2;i++){
            for(int j=2;j<image->h-2;j++){
                int new_pixel = 0;
                for(int k=0;k<5;k++){
                    for(int l=0;l<5;l++){
                        new_pixel += get_pixel(image, i-2+k, j-2+l).r
                        * filter[k][l];
                    }
                }
                set_pixel(new_image, i, j, to_color(new_pixel/256,new_pixel/256, new_pixel/256, new_pixel/256));
            }
        }
    }
    free(image);
    return new_image;
}

SDL_Surface* simple_blur(SDL_Surface* image, int n){
    SDL_Surface* new_image = create_empty(image->w, image->h);
    for(int o=0;o<n;o++){
        for(int i=1;i<image->w-1;i++){
            for(int j=1;j<image->h-1;j++){
                int new_pixel = 0;
                for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        new_pixel += get_pixel(image, i-1+k, j-1+l).r;
                    }
                }
                set_pixel(new_image, i, j, to_color(new_pixel/9,new_pixel/9, new_pixel/9, new_pixel/9));
            }
        }
    }
    free(image);
    return new_image;
}
