#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "../tools/image.h"

#define tmax 360

int** init_matrice(size_t height, size_t width){
	int **A = malloc(sizeof(int*[height]));
    
    for (size_t i = 0; i < height; i++){
        A[i] = malloc(sizeof(int[width]));
    }

	for (size_t i = 0; i < height; i++){
		for (size_t j = 0; j < width ; j++){
			A[i][j] = 0;
		}
	}
	
	return A;
}

void free_matrice(int** A, size_t height){
	for (size_t i = 0; i < height; i++)
		free(A[i]);

	free(A);
}

int max(int** A, size_t rhomax){
    int max = 0;
    for(size_t i = 0; i < tmax; i++){
        for(size_t j = 0; j < rhomax; j++){
            if(A[i][j] > max){
                max = A[i][j];
            }
        }
    }
    return max;
}

SDL_Surface* hough_print(int**A, size_t rhomax){
    SDL_Surface* output = create_empty(tmax, rhomax);
    int valmax = max(A,rhomax);
    Uint8 value;
    for(size_t i = 0; i < tmax; i++){
        for(size_t j = 0; j < rhomax; j++){
	    value = (A[i][j]*255)/valmax;
	    set_pixel(output,i,j,to_color(value,value,value,255));
	}
    }
    return output;
}

void line_trace(SDL_Surface* input, double theta, double rho){
    size_t height = input->h, width = input->w;
    double y;
    size_t i, j;
    for (double x = 0; x < width; x++){
        y = rho - x*cos(theta);
	y /= sin(theta);
	if (x>0 && y>0){
            i = (size_t) x, j = (size_t) y;
	    if (i < height && j < width){
                set_pixel(input, j, i, to_color(255,0,0,255));
	    }
	}
    }
}

void hough_trace(int** A, double x, double y, double rhomax){
    double rho, theta;
    for(size_t t = 0; t < tmax; t++){
        theta = ((double) t)*(M_PI/180);
        rho = (rhomax/2) + x*cos(theta) + y*sin(theta);
        A[t][(size_t) rho] += 1;
    }
}

SDL_Surface* hough_transform(SDL_Surface* input){
    size_t height = input->h, width = input->w;
    size_t rhomax = 2*(height+width);
    int** A = init_matrice(tmax, rhomax);

    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            if(get_pixel(input, i, j).r > 0)
                hough_trace(A, (double) i, (double) j, (double) rhomax);
        }
	//printf("line : %zu\n",i);
    }

    return hough_print(A,rhomax);/*
    int threshold = max(A, rhomax);
    threshold = (3 * threshold)/4;
    printf("threshold = %i\n", threshold);
    for(size_t x = 1; x < tmax; x++){
	for(size_t y = 0; y < rhomax; y++){
	    if (A[x][y] > threshold)
		line_trace(input, (double) x, (double) (y-rhomax/2));
	}
    }
    printf("threshold = %i\n", threshold);
    free_matrice(A,tmax);
    return input;*/
}
