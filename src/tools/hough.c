#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "../tools/image.h"

#define tmax 180
#define margin 50

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
                        set_pixel(input, i, j, to_color(0,0,255,255));
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

int get_intersection(size_t rho1, size_t rho2, size_t theta1, size_t theta2,
                            size_t *i, size_t *j, size_t width, size_t height){
    double rho_1 = (double) rho1, rho_2 = (double) rho2;
    double theta_1 = ((double) theta1)* (M_PI/180), theta_2 = (double) theta2* (M_PI/180);

    double a;
    // y = ax + b
    if (theta_1 == 0 || theta_2 == 0)
        a = sin(theta_2)/cos(theta_2) - sin(theta_1)/cos(theta_1);
    else
        a = cos(theta_2)/sin(theta_2) - cos(theta_1)/sin(theta_2); //opposite because x is negative 
    if (a == 0) // parallel lines
        return 0;
    
    double b;
    if (theta_1 == 0.0 || theta_2 == 0.0)
        b = rho_1/cos(theta_1) - rho_2/cos(theta_2);
    else
        b = rho_1/sin(theta_1) - rho_2/sin(theta_2);
    
    // y = 0
    // ax + b = 0
    // x = -b/a
    double x = -b/a;
    double y;
    if (theta_1 == 0)
        y = rho_1/cos(theta_1);
    else
        y = rho_1/sin(theta_1) - x*cos(theta_1)/sin(theta_1);


    if (x < 0 || y < 0)
        return 0;
    *i = (size_t) x, *j = (size_t) y;
    return (*i < width && *j < height);
}

void trace_intersection(SDL_Surface* input, size_t x, size_t y){
    size_t width = input->w, height = input->h;
    size_t xmax = x + 2, xmin = x - 2;
    size_t ymax = y + 1, ymin = y - 2;

    if (x<=2)
        xmin = x;
    else if (x >= width-3)
        xmax = x;

    if (y<=2)
        ymin = y;
    else if (y >= height-3)
        ymax = y;

    for (size_t i = xmin; i <= xmax; i++)
        for (size_t j = ymin; j <= ymax; j++)
            set_pixel(input, i, j, to_color(255, 0, 0, 255));
}

void hough_trace(int** A, double x, double y, size_t rhomax){
    double rho, theta;
    for(size_t t = 0; t < tmax; t++){
        theta = ((double) t)*(M_PI/180);
        rho = x*cos(theta) + y*sin(theta);
        set_value(A, rhomax, t, rho, get_value(A, rhomax, t, rho) + 1);
    }
}

size_t abs_diff(size_t a, size_t b){
    if (a > b)
        return (a - b);
    return (b - a);
}

int** init_hough(SDL_Surface* input){
    size_t height = input->h, width = input->w;
    size_t rhomax = calc_rhomax(input);
    int** A = init_matrice(rhomax);

    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            if(get_pixel(input, i, j).r > 255/2)
                hough_trace(A, (double) i, (double) j, rhomax);
        }
    }

    return A;
}

void mergeline(int** rholist, unsigned int** thetalist, size_t* length,
                                        unsigned int theta, int rho){
    for (size_t i = 0; i < (*length); i++)
        if (abs_diff((*rholist)[i], rho) < margin && abs_diff((*thetalist)[i], theta) < margin)
            return;
    (*length)++;
    *thetalist = realloc(*thetalist, (*length) * sizeof(unsigned int));
    *rholist = realloc(*rholist, (*length) * sizeof(int));
    //printf("length = %zu\n", *length);
    (*thetalist)[(*length)-1] = theta;
    (*rholist)[(*length)-1] = rho;
}

size_t get_line(int** A, int** rholist, unsigned int** thetalist,
                            size_t thetastart, int rhomax, int threshold){
    size_t length = 0;
    for (unsigned int t = thetastart; t < tmax/2 + thetastart; t++)
        for (int r = -rhomax; r < (int) rhomax; r++)
            if (get_value(A,rhomax, t, r) > threshold)
                mergeline(rholist, thetalist, &length, t, r);
    return length;
}

double findangle(unsigned int* thetalist, size_t length){
    if (length != 0)
        return thetalist[0]*(M_PI/180);
    return 0;
}

double hough_transform(SDL_Surface* input){
    size_t rhomax = calc_rhomax(input);
    int** A;
    // 1st step - Get hough 
    A = init_hough(input);
    // 2nd step - Find hough threshold
    int threshold = 1*max(A, rhomax)/4;
    // 3rd step - Find all the interesting function
    // var_inf -> with 0 <= theta < 90
    unsigned int* thetalist_inf = calloc(0, sizeof(double));
    int* rholist_inf = calloc(0, sizeof(double));
    size_t length_inf = get_line(A, &rholist_inf, &thetalist_inf, 0, rhomax, threshold);

    // var_sup -> with 90 <= theta < 180
    unsigned int* thetalist_sup = calloc(0, sizeof(double));
    int* rholist_sup = calloc(0, sizeof(double));
    size_t length_sup = get_line(A, &rholist_sup, &thetalist_sup, 90, rhomax, threshold);

    for (size_t i = 0; i < length_inf; i++){
        printf("i = %zu\n", i);
        double theta = ((double) thetalist_inf[i])*(M_PI/180);
        double rho = (double) rholist_inf[i];
        line_trace(input, theta, rho);
    }

    for (size_t i = 0; i < length_sup; i++){
        double theta = ((double) thetalist_sup[i])*(M_PI/180);
        double rho = (double) rholist_sup[i];
        line_trace(input, theta, rho);
    }

    // 4th step - Find all intersection point
    //size_t* xlist = calloc(0, sizeof(size_t));
    //size_t* ylist = calloc(0, sizeof(size_t));
    //size_t length2 = 0;

    /*
    for(size_t i = 0; i < length; i++){
        for(size_t j = i+1; j < length; j++){
            size_t x = 17, y = 41;
            if(get_intersection(rholist[i], rholist[j], thetalist[i], thetalist[j], &x, &y, width, height)){
                trace_intersection(input, y, x);
                //set_pixel(input, y, x, to_color(255,0,0,255));
                //length2++;
                //xlist = realloc(xlist, length*sizeof(size_t));
                //xlist[length2-1] = x;
                //ylist = realloc(ylist, length*sizeof(size_t));
                //ylist[length2-1] = y;
            }
        }
    }

    // 5th step - Get the index of the highest and lowest interaction function

    // 6th step - Erase all detected line by covering them in black

    // 7th step - Cut the picture to only have the grid

    // nth step - Free dynamic memory allocation
    */

    //free(xlist);
    //free(ylist);

    //free(thetalist_inf);
    //free(thetalist_sup);
    //free(rholist_sup);
    //free(rholist_inf);
    
    free_matrice(A);
    printf("hi bitches!\n");
    return findangle(thetalist_inf,length_inf);
}
*/