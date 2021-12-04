#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "../tools/image.h"

#define tmax 180

/*size_t calc_rhomax(SDL_Surface* image){
    return (size_t) sqrt(image->w * image->w + image->h * image->h);
}

int get_value(int **A, size_t rhomax, unsigned int theta, int rho){
    return A[theta][(size_t) (rho+rhomax)];
}

void set_value(int **A, size_t rhomax, unsigned int theta, int rho,
                                                                int value){
    A[theta][(size_t) (rho+rhomax)] = value;
}

int** init_matrice(size_t rhomax){
	int **A = malloc(sizeof(int*[tmax]));

    for (size_t i = 0; i < tmax; i++){
        A[i] = malloc(sizeof(int[rhomax*2]));
    }

	for (size_t i = 0; i < tmax; i++){
		for (size_t j = 0; j < rhomax*2; j++){
			A[i][j] = 0;
		}
	}

	return A;
}

void free_matrice(int** A){
	for (size_t i = 0; i < tmax; i++)
		free(A[i]);

	free(A);
}

int max(int** A, size_t rhomax){
    int max = 0;
    for(size_t i = 0; i < tmax; i++){
        for(size_t j = 0; j < rhomax*2; j++){
            if(A[i][j] > max){
                max = A[i][j];
            }
        }
    }
    return max;
}

void line_trace(SDL_Surface* input, double theta, double rho){
    size_t height = input->h, width = input->w;
    double x, y;
    size_t i, j;
    for (x = 0; x < width; x++){
        y = rho - x*cos(theta);
        y /= sin(theta); //y*sin(theta) = rho - x*cos(theta)
        if (x>0 && y>0){ 
                i = (size_t) x;
                j = (size_t) y;
                if (i < width && j < height){
                        set_pixel(input, i, j, to_color(255,0,0,255));
                }
        }
    }
    for (y = 0; y < height; y++){
        x = rho - y*sin(theta);
        x /= cos(theta); //x*cos(theta) = rho - y*sin(theta)
        if (x>0 && y>0){
                i = (size_t) x;
                j = (size_t) y;
                if (i < width && j < height){
                        set_pixel(input, i, j, to_color(0,255,0,255));
                }
        }
    }
}

int get_intersection(size_t rho1, size_t rho2, size_t theta1, size_t theta2){
    double rho_1 = (double) rho1, rho_2 = (double) rho2;
    double theta_1 = (double) theta1, theta_2 = (double) theta2;
    return 0;
}

void hough_trace(int** A, double x, double y, size_t rhomax){
    double rho, theta;
    for(size_t t = 0; t < tmax; t++){
        theta = ((double) t)*(M_PI/180);
        rho = x*cos(theta) + y*sin(theta);
        set_value(A, rhomax, t, rho, get_value(A, rhomax, t, rho) + 1);
    }
}


double hough_transform(SDL_Surface* input){
    size_t height = input->h, width = input->w;
    size_t rhomax = calc_rhomax(input);
    int** A = init_matrice(rhomax);

    // 1st step - Get hough 
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            if(get_pixel(input, i, j).r > 255/2)
                hough_trace(A, (double) i, (double) j, rhomax);
        }
    }

    // 2nd step - Find hough threshold
    int threshold = max(A, rhomax);

    // 3rd step - Find all the interesting function
    size_t* thetalist = calloc(0, sizeof(size_t));
    size_t* rholist = calloc(0, sizeof(size_t));
    size_t length = 0;

    for(unsigned int t = 0; t < tmax; t++){
        for(int r = -rhomax; r < (int) rhomax; r++){
            if (get_value(A, rhomax, t, r) > threshold){
                length++;
                thetalist = realloc(thetalist, length * sizeof(size_t));
                thetalist[length-1] = t;
                rholist = realloc(rholist, length * sizeof(size_t));
                rholist[length-1] = r;
            }
        }
    }

    // 4th step - Find all intersection point
    size_t* xlist = calloc(0, sizeof(size_t));
    size_t* ylist = calloc(0, sizeof(size_t));
    size_t length2 = 0;

    for(size_t i = 0; i < length; i++){
        for(size_t j = i+1; j < length; j++){
            if(get_intersection(rholist[i], rholist[j], thetalist[i], thetalist[j])){
                
            }
        }
    }

    // test interaction function
    for (size_t i = 0; i < length2; i++)
        set_pixel(input, xlist[i], ylist[i], to_color(0,0,255,255))

    // 5th step - Get the index of the highest and lowest interaction function

    // 6th step - Erase all detected line by covering them in black

    // 7th step - Cut the picture to only have the grid

    // nth step - Free dynamic memory allocation
    double thetamin = 0;
    if (length != 0)
        thetamin = thetalist[0]*(M_PI/180);
    free(thetalist);
    free(rholist);
    free_matrice(A);

    return thetamin;
    return 0;
}
*/