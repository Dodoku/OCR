#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <SDL2/SDL_surface.h>

typedef struct {

    int nbColumns;
    int nbLines;

    double **data;
} Data;

typedef struct {

    int expectedNumber;
    SDL_Surface *image;
} TrainData;

Data load_data(char *path);
void save_data(Data *data, char *path);

Network load_network(char *path);
void save_network(Network *net, char *path);

FILE *open_train(char *path);
TrainData read_train_image(FILE *file);

int countLines(FILE *fp);

#endif
