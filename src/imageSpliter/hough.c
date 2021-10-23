#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "../tools/image.h"

#define tmax 1800

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

void max(int** A, size_t* x, size_t* y, size_t rhomax){
    int max = 0;
    for(size_t i = 0; i < tmax; i++){
        for(size_t j = 0; j < rhomax; j++){
            if(A[i][j] > max){
                *x = i;
                *y = j;
                max = A[i][j];
            }
        }
    }
}

void line_trace(SDL_Surface* input, double theta, double rho){
    size_t height = input->h, width = input->w;
    double y;
    size_t i, j;
    for (double x = 0; x < width; x++){
        y = (rho - x*cos(theta))/sin(theta);
	y =-y;
	printf("y = %f\n", y);
	if (x>0 && y>0){
            i = (size_t) x, j = (size_t) y;
	    if (i < height && j < width){
                set_pixel(input, i, j, to_color(255,0,0,255));
		printf("hey!\n");
	    }
	}
    }
}

void hough_trace(int** A, double x, double y, double rhomax){
    double rho, theta;
    for(size_t t = 0; t < tmax; t++){
        theta = ((double) t/10)*(M_PI/180);
        rho = (rhomax/2) + x*cos(theta) + y*sin(theta);
        A[t][(size_t) rho] += 1;
    }
}

SDL_Surface* hough_transform(SDL_Surface* input){
    size_t height = input->h, width = input->w;
    size_t rhomax = 2*(height+width);
    int** A = init_matrice(tmax, rhomax);
    //SDL_Surface* output = create_empty(width, height);

    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            if(get_pixel(input, i, j).r > 0)
                hough_trace(A, (double) i, (double) j, (double) rhomax);
        }
	printf("line : %zu\n",i);
    }

    size_t x = 0, y = 0;
    size_t *i = &x, *j = &y;
    max(A, i, j, rhomax);
    y -= rhomax/2;
    line_trace(input, (double) x,(double) y);
    free_matrice(A,tmax);
    return input;
}
