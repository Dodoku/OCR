#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "../tools/image.h"


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

void print_matrice(int**A, size_t height, size_t width){
	for (size_t i = 0; i < height; i++){
		printf("| ");
        for (size_t j = 0; j < width ; j++){
			printf("%i | ",A[i][j]);
        }
        printf("\n");
	}
}

SDL_Surface* better_print(int** A, size_t height, size_t width){
    SDL_Surface* print = create_empty(width, height);
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++){
            int color = A[j][i];
            if (color>255)
                color = 255;
            set_pixel(print, j, i, to_color(color, color, color, 255));
        }
    }
    return print;
}

void place_point(int** A, size_t x, size_t y, int max){
    double rho, theta;
    for (size_t t = 0; t < 360; t++){
        theta = t*(M_PI/180);
        rho = max + x*cos(theta) + y*sin(theta);
        A[(int)rho][t] += 1;
    }
}

void mapping(SDL_Surface* image, int** A, int mid){
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            Uint8 value = get_pixel(image, i, j).r;
            if (value == 255)
                place_point(A, i, j, mid);
        }
    }
}

void hough_transform(SDL_Surface* image){
    //init values
    size_t height = image->h, width = image->w;
    size_t rhomax = 2*(height+width);
    int** A = init_matrice(rhomax, 360);
    //mapping
    mapping(image, A, rhomax/2);
    //print
    //SDL_Surface* print = better_print(A, rhomax, 180);
    //save(print, "tests/assets/sinus.jpeg");
    //free values

    free_matrice(A, rhomax);
}
