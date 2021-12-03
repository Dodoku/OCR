#include <stdio.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"
#include "../imageProcess/grayscale.h"

#define SIGMA 1
#define KERNEL 2

void gfilter(double filter[KERNEL*2+1][KERNEL*2+1], int row, int column, double sigma){
    float coordsum = 0;
    float constant = 2.0 * sigma * sigma;

    for(int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            coordsum = (i-KERNEL-1)*(i-KERNEL-1) + (j-KERNEL-1)*(j-KERNEL-1);
            filter[i][j] = (exp(-coordsum/constant)) / (M_PI * constant);
        }
    }
}

SDL_Surface* gaussian(SDL_Surface* input, size_t k){
    size_t width = input->w, height = input->h;

    double filter[2*k+1][2*k+1];
    for (size_t i = 0; i < 2*k+1; i++)
        for (size_t j = 0; j < 2*k+1; j++)
            filter[i][j] = -1.0;

    gfilter(filter, 2*k+1, 2*k+1, SIGMA);
    
    SDL_Surface* gauss = create_empty(width, height);

    for (size_t i = k; i < width - k; i++){
        for (size_t j = k; j < height - k; j++){
            double sum = 0;
            for (size_t x = 0; x < 2*k+1; x++){
                for (size_t y = 0; y < 2*k+1; y++){
                    double temp = (double) get_pixel(input, i+x-k, j+y-k).r;
                    sum += filter[x][y] * temp;
                }
            }
            set_pixel(gauss, i, j, to_color((int) sum,(int) sum,(int) sum,255));
        }
    }

    return gauss;
}

SDL_Color isedge(SDL_Surface* input, size_t x, size_t y){
    if (get_pixel(input, x, y).r != 0)
        return to_color(0,0,0,255);
    for (size_t i = x-1; i<= x+1; i++)
        for (size_t j = y-1; j <= y+1; j++)
            if (get_pixel(input, i, j).r != 0)
                return to_color(255,255,255,255);
    return to_color(0,0,0,255);
}

SDL_Surface* edgemap(SDL_Surface* input){
    size_t width = input->w-2, height = input->h-2;
    SDL_Surface* edge = create_empty(width, height);
    for (size_t i = 1; i < width+1; i++)
        for (size_t j = 1; j < height+1; j++)
            set_pixel(edge, i-1, j-1, isedge(input, i, j));
    return edge;
}

/*
void sobel(SDL_Surface* input){
    double xfilter[][] = {
        {-1.0, 0, 1.0},
        {-2.0, 0, 2.0},
        {-1.0, -2.0, 1.0}
    };
    double yfilter[][] = {
        {1.0, 2.0, 1.0},
        {0, 0, 0},
        {-1.0, -2.0, -1.0}
    };

    // Limit Size
    
}

void nonmaxsupp(){

}

void threeshold(SDL_Surface* input, int low, int high){
    if(low>255)
        low = 255;
    if(high>255)
        high = 255;

    for(){
        for(){
            if (get_pixel(input, i, j)>high)
                set_pixel(input, i, j, to_color(255,255,255,255));
            else if (get_pixel(input, i, j)<low)
                set_pixel(input, i, j, to_color(0,0,0,255));
            else{
                int anyhigh = 0, anybetween = 0;
                for(){
                    for(){
                        if ()
                            continue;
                        else{
                            if (){
                                set_pixel(input, i, j, to_color(255,255,255,0));
                                anyhigh = 1;
                                break;
                            }
                            else if ()
                                anybetween = 1;
                        }
                    }
                    if(anyhigh)
                        break;
                }
                if (!anyhigh & anybetween)
            }
        }
    }
}


SDL_Surface* canny(SDL_Surface* input){
    SDL_Surface* gray = to_grayscale(input);
    return gaussian(gray,KERNEL);
}

*/