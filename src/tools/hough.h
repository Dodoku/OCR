#ifndef HOUGH
#define HOUGH

#include <SDL2/SDL.h>

struct tuple{
    unsigned int theta;
    int rho;
};

size_t calc_rhomax(SDL_Surface* image);

int get_value(int **A, size_t rhomax, unsigned int theta, int rho);

void set_value(int **A, size_t rhomax, unsigned int theta, int rho,
                                                                int value);

int** init_matrice(size_t rhomax);

void free_matrice(int** A);

int max(int** A, size_t rhomax);

void line_trace(SDL_Surface* input, double theta, double rho);

int get_intersection(size_t rho1, size_t rho2, size_t theta1, size_t theta2,
                            size_t *i, size_t *j, size_t width, size_t height);

void trace_intersection(SDL_Surface* input, size_t x, size_t y);

void hough_trace(int** A, double x, double y, size_t rhomax);

size_t abs_diff(size_t a, size_t b);

int** init_hough(SDL_Surface* input);

void mergeline(int** rholist, unsigned int** thetalist, size_t* length,
                                        unsigned int theta, int rho);

size_t get_line(int** A, int** rholist, unsigned int** thetalist,
                                         int rhomax, int threshold);

void swap(int* a, int* b, unsigned int* i, unsigned int* j);

size_t partition(int** R, unsigned int** T, size_t l, size_t h);

void quickSort(int** R,  size_t l, size_t h);

double findangle(unsigned int* thetalist, size_t length);

double hough_transform(SDL_Surface* input);

#endif
