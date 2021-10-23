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

SDL_Color color_flex(SDL_Color input){
    SDL_Color output;
    if(input.r > 5){
	output.a = input.a;
	output.r = input.r-1;
	output.g = input.g;
	output.b = input.b;
	return output;
    }
    if(input.g > 5){
	output.a = input.a;
	output.r = 0;
	output.g = input.g-1;
	output.b = input.b;
	return output;
    }
    if(input.b > 5){
	output.a = input.a;
	output.r = 0;
	output.g = 0;
	output.b = input.b-1;
	return output;
    }
    return input;
}

void hough_trace(SDL_Surface* output, double x, double y, double rhomax){
    double rho, theta;
    for(size_t t = 0; t < 3600; t++){
        theta = ((double) t/10)*(M_PI/180);
        rho = (rhomax/2) + x*cos(theta) + y*sin(theta);
        SDL_Color pixel = color_flex(get_pixel(output, t, (size_t) rho));
        set_pixel(output, t, (size_t) rho, pixel);
    }
}

SDL_Surface* hough_mapping(SDL_Surface* input){
    size_t height = input->h, width = input->w;
    size_t rhomax = 2*(height+width);
    SDL_Surface* output = create_empty(3600, rhomax);
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            if(get_pixel(input, i, j).r > 0)
                hough_trace(output, (double) i, (double) j, (double) rhomax);
        }
	printf("%zu\n",i);
    }
    return output;
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

SDL_Surface* function_print(){
    SDL_Surface* print = create_empty(3600,4000);
    double rho, theta;
    for (size_t t = 0; t < 3600; t++){
        theta = (((double)t)/10)*(M_PI/180);
        rho = 2000.0 + 1000.0*cos(theta) + 1000.0*sin(theta);
        printf("rho = %f and theta = %zu\n",rho,t);
        set_pixel(print, t, (int)rho, to_color(0,0,0,255));
    }
    return print;
}
