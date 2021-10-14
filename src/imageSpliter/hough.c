#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>


/*
 * Initialize a height * width matrix with it's value to 0
 * @param height (size_t) : Height of the new matrix
 * @param width (size_t) : Width of the new matrix
 * @return (int**) : New matrix
 * @author Dylan INNOU
 */
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

/*
 * 
 * @param A (int**) : 
 * @param height (size_t) : 
 * @param width (size_t) : 
 * @return (void) : 
 * @author Dylan INNOU
 */
void print_matrice(int**A, size_t height, size_t width){
	for (size_t i = 0; i < height; i++){
		for (size_t j = 0; j < width ; j++){
			printf("A[%zu][%zu] = %i\n",i,j,A[i][j]);
		}
	}
}

SDL_Surface* render_line(SDL_Surface image){
}


void mapping(SDL_Surface* image, int** A){
    for (size_t i = 0; i < image->w; i++) {
        for (size_t j = 0; j < image->h; j++) {
            Uint8 value = get_pixel(image, i, j).r;
            if (value == 255)
                place_point(i, j);
        }
    }
}

void place_point(int** A, size_t x, size_t y){
    size_t rho;
	for (size_t theta = 0; theta < 180; theta++){
        rho = x*cos(theta) + y*sin(theta);
        A[rho][theta] += 1;
    }
}

void hough_transform(SDL_Surface* image){
    int** A = init_matrice(#TODO);
    mapping(image, A);
    //Interpretation of yield line
    //Infite to finite line

void free_matrice(int** A, size_t height){
	for (size_t i = 0; i < height; i++)
		free(A[i]);

	free(A);
}
