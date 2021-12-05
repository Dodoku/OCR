#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <math.h>

#include "../tools/image.h"
#include "../tools/hough.h"

#define tmax 180
#define margin 50

size_t calc_rhomax(SDL_Surface* image){
    return (size_t) sqrt(image->w * image->w + image->h * image->h);
}

int get_value(int **A, size_t rhomax, unsigned int theta, int rho){
    return A[theta][(size_t) (rho+rhomax)];
}

void set_value(int **A, size_t rhomax, unsigned int theta, int rho,
                                                                int value){
    A[theta][(size_t) (rho+rhomax)] = value;
}

double ttt(unsigned int theta){
    return ((double) theta)*(M_PI/180);
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
        if (x>=0 && y>=0){ 
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

void line_trace_v(SDL_Surface* input, double theta, double rho, SDL_Color color){
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
                set_pixel(input, i, j, color);
            }
        }
    }
}

void line_trace_h(SDL_Surface* input, double theta, double rho, SDL_Color color){
    size_t height = input->h, width = input->w;
    double x, y;
    size_t i, j;
    for (y = 0; y < height; y++){
        x = rho - y*sin(theta);
        x /= cos(theta); //x*cos(theta) = rho - y*sin(theta)
        if (x>0 && y>0){
            i = (size_t) x;
            j = (size_t) y;
            if (i < width && j < height){
                set_pixel(input, i, j, color);
            }
        }
    }
}

// when the line is vertical, because we want x = 0 and get the height of the line
double height_line(int r, unsigned int t){
    double rho = (double) r;
    double theta = ttt(t);
    return rho/sin(theta);
}

// when the line is horizontal, because we want y = 0 and get the 
double side_line(int r, unsigned int t){
    double rho = (double) r;
    double theta = ttt(t);
    return rho/cos(theta);
}

int get_intersection(int rho1, int rho2, size_t theta1, size_t theta2,
                            size_t *i, size_t *j, size_t width, size_t height){
    double rho_1 = (double) rho1, rho_2 = (double) rho2;
    double theta_1 = ttt(theta1), theta_2 = ttt(theta2);

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
    size_t width =  input->w, height = input->h;
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
            set_pixel(input, i, j, to_color(255, 127, 127, 255));
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

unsigned int get_color_neighboor(SDL_Surface* input, int x, int y){
    int width = input->w, heigth = input->h;
    int xmin = x - 2, xmax = x + 2;
    int ymin = y - 2, ymax = y + 2;

    if (xmin < 0)
        xmin = x;
    else if (xmax >= width)
        xmax = x;
    if (ymin < 0)
        ymin = y;
    else if (ymax >= heigth)
        ymax = y;
    
    int sum = 0;
    for (int i = xmin; i < xmax; i++)
        for (int j = ymin; j < ymax; j++)
            sum += get_pixel(input, i, j).r;
    return sum;
}

void mergeline(int** rholist, unsigned int** thetalist, size_t* length,
                                        unsigned int theta, int rho){
    for (size_t i = 0; i < (*length); i++)
        if (abs_diff((*rholist)[i], rho) < margin &&
            abs_diff((*thetalist)[i], theta) < margin)
            return;
    (*length)++;
    *thetalist = realloc(*thetalist, (*length) * sizeof(unsigned int));
    *rholist = realloc(*rholist, (*length) * sizeof(int));
    (*thetalist)[(*length)-1] = theta;
    (*rholist)[(*length)-1] = rho;
}

size_t get_line(int** A, int** rholist, unsigned int** thetalist,
                                         int rhomax, int threshold){
    size_t length = 0;
    for (unsigned int t = 0; t < tmax; t++)
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

// step is positive if we want the line to be the upper part of the rectangle
void fix_square0(SDL_Surface* input, struct tuple* line1, struct tuple* line2, size_t i, unsigned int** tlist, int** rlist, int step){
    size_t width = input->w, height = input->h;
    size_t x = 0, y = 0;

    unsigned char index = 20;
    unsigned char error = 5;
    if (!get_intersection(line1->rho, line2->rho, line1->theta, line2->theta, &x, &y, width, height)){
        return;
    }
    while (index > 0){
        if (get_color_neighboor(input, x, y) < 127){ //the pixel is therefore black
            error--;
            if (error == 0){
                i+=step;
                printf("val i = %zu\n", i);
                line1->rho = (*rlist)[i];
                line1->theta = (*tlist)[i];
                if (!get_intersection(line1->rho, line2->rho, line1->theta, line2->theta, &x, &y, width, height))
                    return;
                error = 5;
                index = 20;
                continue;
            } //the line has been cutted for more than error pixel, it shouldn't be taken into account
        }
        index--;
        y+=step;
    }
}

// step is positive if we want the line to be going to the right part of the rectangle
void fix_square90(SDL_Surface* input, struct tuple* line1, struct tuple* line2, size_t i, unsigned int** tlist, int** rlist, int step){
    size_t width = input->w, height = input->h;
    size_t x = 0, y = 0;

    unsigned char index = 20;
    unsigned char error = 5;
    if (!get_intersection(line1->rho, line2->rho, line1->theta, line2->theta, &x, &y, width, height)){
        return;
    }
    while (index > 0){
        if (get_color_neighboor(input, x, y) < 127){ //the pixel is therefore black
            error--;
            if (error == 0){
                i+=step;
                printf("val i = %zu\n", i);
                line1->rho = (*rlist)[i];
                line1->theta = (*tlist)[i];
                if (!get_intersection(line1->rho, line2->rho, line1->theta, line2->theta, &x, &y, width, height))
                    return;
                error = 5;
                index = 20;
                continue;
            } //the line has been cutted for more than error pixel, it shouldn't be taken into account
        }
        index--;
        x+=step;
    }
}

void get_rect(SDL_Surface* input, unsigned int** thetalist_inf, unsigned int** thetalist_sup, int** rholist_inf, int** rholist_sup, size_t length_inf, size_t length_sup){
    struct tuple up;
    up.theta = (*thetalist_inf)[0];
    up.rho = (*rholist_inf)[0];
    struct tuple down;
    down.theta = (*thetalist_inf)[length_inf-1];
    down.rho = (*rholist_inf)[length_inf-1];
    struct tuple left;
    left.theta = (*thetalist_sup)[0];
    left.rho = (*rholist_sup)[0];
    struct tuple right;
    right.theta = (*thetalist_sup)[length_sup-1];
    right.rho = (*rholist_sup)[length_sup-1];

    //fix_square0(input, &up, &left, 0, thetalist_inf, rholist_inf, 1);
    //fix_square90(input, &left, &down, 0, thetalist_sup, rholist_sup, 1);
    //fix_square0(input, &down, &right, length_inf-1, thetalist_inf, rholist_inf, -1);
    //fix_square90(input, &right, &up, length_sup-1, thetalist_sup, rholist_sup, -1);

    line_trace_h(input, ttt(up.theta), (double) up.rho, to_color(255,0,0,255));
    line_trace_h(input, ttt(down.theta), (double) down.rho, to_color(0,255,0,255));
    line_trace_v(input, ttt(left.theta), (double) left.rho, to_color(0,0,255,255));
    line_trace_v(input, ttt(right.theta), (double) right.rho, to_color(255,0,255,255));
}

void swap(int* a, int* b, unsigned int* i, unsigned int* j){
    int temp = *a;
    *a = *b;
    *b = temp;

    unsigned int eff = *i;
    *i = *j;
    *j = eff;
}

int partition0(int** R, unsigned int** T, int l, int h){
    double x = side_line((*R)[h], (*T)[h]);
    int i = (l - 1);
 
    for (int j = l; j <= h - 1; j++) { 
        if (side_line((*R)[j], (*T)[j]) <= x) {
            i++;
            swap(&(*R)[i], &(*R)[j], &(*T)[i], &(*T)[j]);
        }
    }
    swap(&(*R)[i + 1], &(*R)[h], &(*T)[i + 1], &(*T)[h]);
    return (i + 1);
}

void quickSort0(int** R, unsigned int** T,  int l, int h){
    if (l < h) {
        int p = partition0(R, T, l, h);
        quickSort0(R, T, l, p - 1);
        quickSort0(R, T, p + 1, h);
    }
}

int partition90(int** R, unsigned int** T, int l, int h){
    double x = height_line((*R)[h], (*T)[h]);
    size_t i = (l - 1);
 
    for (int j = l; j <= h - 1; j++) {
        if (height_line((*R)[j], (*T)[j]) <= x) {
            i++;
            swap(&(*R)[i], &(*R)[j], &(*T)[i], &(*T)[j]);
        }
    }
    swap(&(*R)[i + 1], &(*R)[h], &(*T)[i + 1], &(*T)[h]);
    return (i + 1);
}

void quickSort90(int** R, unsigned int** T,  int l, int h){
    if (l < h) {
        int p = partition90(R, T, l, h);
        quickSort90(R, T, l, p - 1);
        quickSort90(R, T, p + 1, h);
    }
}
/*
double hough_transform(SDL_Surface* input, ){
    size_t width = input->w, height = input->h;
    size_t rhomax = calc_rhomax(input);
    int** A;
    // 1st step - Get hough
    A = init_hough(input);
    // 2nd step - Find hough threshold
    int threshold = 1*max(A, rhomax)/4;
    // 3rd step - Find all the interesting function
    unsigned int* thetalist = calloc(0, sizeof(unsigned int));
    int* rholist = calloc(0, sizeof(int));
    size_t length = get_line(A, &rholist, &thetalist, rhomax, threshold);
    // find the angle the picture is lead into
    double thetamin = findangle(thetalist,length);
    
    unsigned int* thetalist_inf = calloc(0, sizeof(unsigned int));
    int* rholist_inf = calloc(0, sizeof(int));
    size_t length_inf = 0;
    unsigned int* thetalist_sup = calloc(0, sizeof(unsigned int));
    int* rholist_sup = calloc(0, sizeof(int));
    size_t length_sup = 0;

    for (size_t i = 0; i < length; i++){
        if (thetalist[i]-thetalist[0] < 80 || thetalist[i]-thetalist[0] >= 170){
            length_inf++;
            thetalist_inf = realloc(thetalist_inf, length_inf * sizeof(unsigned int));
            rholist_inf = realloc(rholist_inf, length_inf * sizeof(int));
            thetalist_inf[length_inf-1] = thetalist[i];
            rholist_inf[length_inf-1] = rholist[i];
        }
        else{
            length_sup++;
            thetalist_sup = realloc(thetalist_sup, length_sup * sizeof(unsigned int));
            rholist_sup = realloc(rholist_sup, length_sup * sizeof(int));
            thetalist_sup[length_sup-1] = thetalist[i];
            rholist_sup[length_sup-1] = rholist[i];
        }
    }
    
    quickSort0(&rholist_inf, &thetalist_inf, 0, length_inf-1);
    quickSort90(&rholist_sup, &thetalist_sup, 0, length_sup-1);

    for (size_t i = 0; i < length_inf; i++){
        line_trace(input, ttt(thetalist_inf[i]), rholist_inf[i]);
    }
    for (size_t j = 0; j < length_sup; j++){
        line_trace(input, ttt(thetalist_sup[j]), rholist_sup[j]);
    }

    //get_rect(input, &thetalist_inf, &thetalist_sup, &rholist_inf, &rholist_sup, length_inf, length_sup);

    free(thetalist);
    free(rholist);
    free(thetalist_inf);
    free(rholist_inf);
    free(thetalist_sup);
    free(rholist_sup);
    
    free_matrice(A);
    return thetamin;
}
*/

double hough_transform(SDL_Surface* input, unsigned int** thetalist_inf,
                                            unsigned int** thetalist_sup,
                                            int** rholist_inf,
                                            int** rholist_sup,
                                            size_t* length_inf,
                                            size_t* length_sup){
    size_t rhomax = calc_rhomax(input);
    int** A;
    // 1st step - Get hough
    A = init_hough(input);
    // 2nd step - Find hough threshold
    int threshold = 1*max(A, rhomax)/4;
    // 3rd step - Find all the interesting function
    unsigned int* thetalist = calloc(0, sizeof(unsigned int));
    int* rholist = calloc(0, sizeof(int));
    size_t length = get_line(A, &rholist, &thetalist, rhomax, threshold);
    // find the angle the picture is lead into
    double thetamin = findangle(thetalist,length);

    for (size_t i = 0; i < length; i++){
        if (thetalist[i]-thetalist[0] < 80 || thetalist[i]-thetalist[0] >= 170){
            (*length_inf)++;
            *thetalist_inf = realloc((*thetalist_inf), (*length_inf) * sizeof(unsigned int));
            *rholist_inf = realloc((*rholist_inf), (*length_inf) * sizeof(int));
            (*thetalist_inf)[(*length_inf)-1] = thetalist[i];
            (*rholist_inf)[(*length_inf)-1] = rholist[i];
        }
        else{
            (*length_sup)++;
            *thetalist_sup = realloc((*thetalist_sup), (*length_sup) * sizeof(unsigned int));
            *rholist_sup = realloc((*rholist_sup), (*length_sup) * sizeof(int));
            (*thetalist_sup)[(*length_sup)-1] = thetalist[i];
            (*rholist_sup)[(*length_sup)-1] = rholist[i];
        }
    }
    
    quickSort0(rholist_inf, thetalist_inf, 0, (*length_inf)-1);
    quickSort90(rholist_sup, thetalist_sup, 0, (*length_sup)-1);

    free(thetalist);
    free(rholist);
    
    free_matrice(A);
    return thetamin;
}
