#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "../tools/image.h"

#define tmax 1800

long** init_matrice(size_t height, size_t width){
	long **A = malloc(sizeof(long*[height]));
    
    for (size_t i = 0; i < height; i++){
        A[i] = malloc(sizeof(long[width]));
    }

	for (size_t i = 0; i < height; i++){
		for (size_t j = 0; j < width ; j++){
			A[i][j] = 0;
		}
	}
	
	return A;
}

void free_matrice(long** A, size_t height){
	for (size_t i = 0; i < height; i++)
		free(A[i]);

	free(A);
}

long max(long** A, size_t rhomax){
    long max = 0;
    for(size_t i = 0; i < tmax; i++){
        for(size_t j = 0; j < rhomax; j++){
            if(A[i][j] > max)
                max = A[i][j];
        }
    }
    return max;
}

void line_trace(SDL_Surface* input, double theta, double rho){
    size_t height = input->h, width = input->w;
    double y;
    size_t i, j;
    for (double x = 0; x < width; x++){
        y = (rho - x*cos(theta))/sin(theta);
        if (x>0 && y>0){
            i = (size_t) x, j = (size_t) y;
            if (i < height && j < width)
                set_pixel(input, i, j, to_color(255,0,0,255));
        }
    }
}

void hough_lines(SDL_Surface* input, long** A, size_t rhomax, long threshold){
    double rho;
    for(size_t i = 0; i < tmax; i++){
        for(size_t j = 0; j < rhomax; j++){
	    //printf("i = %zu ; j = %zu\n ; tmax = %u ; rhomax = %zu\n; val = %i\n", i, j,tmax,rhomax, A[i][j]);
	    if((A[i][j]) > threshold){
                rho = ((double) j) - ((double)rhomax)/2;
                line_trace(input, (double) i, rho);
            }
        }
    }
}

void hough_trace(long** A, double x, double y, double rhomax){
    double rho, theta;
    for(size_t t = 0; t < tmax; t++){
        theta = ((double) t/10)*(M_PI/180);
        rho = (rhomax/2) + x*cos(theta) + y*sin(theta);
		size_t r = (size_t) rho;
		A[t][r] += 1;
    }
}

SDL_Surface* hough_transform(SDL_Surface* input){
    size_t height = input->h, width = input->w;
    size_t rhomax = 2*(height+width);
    long** A = init_matrice(tmax, rhomax);
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            if(get_pixel(input, i, j).r > 0)
                hough_trace(A, (double) i, (double) j, (double) rhomax);
        }
    }

    long threshold = (max(A, rhomax))/2;
    hough_lines(input, A, rhomax, threshold);
    free_matrice(A,tmax);
    return input;
}
