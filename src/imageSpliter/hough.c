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

void print_matrice(int**A, size_t height, size_t width){
	for (size_t i = 0; i < height; i++){
		for (size_t j = 0; j < width ; j++){
			printf("A[%zu][%zu] = %i\n",i,j,A[i][j]);
		}
	}
}

/*
SDL_Surface* render_line(SDL_Surface image){
}
*/

SDL_Surface* better_print(int** A, size_t height, size_t width){
    SDL_Surface print = create_empty(height, width);
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++){
            int color = A[i][j];
            if (color>255)
                color = 255;
            set_pixel(print, i, j, to_color(color, color, color, 255));
        }
    }
    return print;
}

void mapping(SDL_Surface* image, int** A, int mid){
    for (size_t i = 0; i < image->w; i++) {
        for (size_t j = 0; j < image->h; j++) {
            Uint8 value = get_pixel(image, i, j).r;
            if (value == 255)
                place_point(A, i, j, mid);
        }
    }
}

void place_point(int** A, size_t x, size_t y, int max){
    double rho;
	for (double theta = 0; theta < 180; theta++){
        theta = theta*(M_PI/180);
        rho = max x*cos(theta) + y*sin(theta);
        A[rho][theta] += 1;
    }
}

void hough_transform(SDL_Surface* image){
    size_t height = image->h;
    size_t weight = image->w;
    int** A = init_matrice(2*(height + weight), 180);
    mapping(image, A, h+w);
    SDL_Surface* print = better_print(A, 2*(height + weight), 180);
    save(*print, "../../tests/assets/sinus.jpeg");
    free_matrice(A, 2*(height + weight));
}

void free_matrice(int** A, size_t height){
	for (size_t i = 0; i < height; i++)
		free(A[i]);

	free(A);
}
