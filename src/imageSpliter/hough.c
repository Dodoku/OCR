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
			printf("%i |",A[i][j]);
        }
        printf("\n");
	}
}

/*
SDL_Surface* render_line(SDL_Surface image){
}
*/

SDL_Surface* better_print(int** A, size_t height, size_t width){
    SDL_Surface* print = create_empty(height, width);
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

void place_point(int** A, size_t x, size_t y, int max){
    double rho;
	double theta;
    for (double t = 0; t < 180; t++){
        theta = t*(M_PI/180);
        rho = max + x*cos(theta) + y*sin(theta);
        printf("rho = %f ; theta = %f");
        A[(int)rho][(int)theta] += 1;
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

void hough_transform(){
    SDL_Surface* image = load("tests/assets/grey.jpeg");
    printf("part1\n");
    size_t height = image->h;
    size_t width = image->w;
    int** A = init_matrice(2*(height + width), 180);
    printf("part2\n");
    mapping(image, A, height+width);
    printf("part3\n");
    SDL_Surface* print = better_print(A, 2*(height + width), 180);
    printf("part4\n");
    save(print, "tests/assets/sinus.jpeg");
    free_matrice(A, 2*(height + width));
}

