#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "dataLoader.h"
#include "neuralNetwork.h"

Data load_data(char *path){
    Data data;

    FILE *fp;
    
    char *c = NULL;
    size_t n;

    int line = 0;
    int column = 0;

    fp = fopen(path, "r");
    if (!fp)
        errx(1, "Couldn't open %s\n", path);

    fscanf(fp, "%i %i |", &data.nbLines, &data.nbColumns);
    data.data = malloc(data.nbLines * sizeof(*data.data));

    for(int i = 0; i < data.nbLines; i++)
        data.data[i] = malloc(data.nbColumns * sizeof(**data.data));

    while(!feof(fp)){
        if (getdelim(&c, &n, ' ', fp) > 1){
            data.data[line][column] = atof(c);
            column++;
        }else if(getdelim(&c, &n, '\n', fp) > 1){
            data.data[line][column] = atof(c);
            line++;
            column = 0;
        }
    }

    if(c)
        free(c);

    fclose(fp);
    return data;
}

void save_data(Data *data, char *path){
    FILE *fp;

    fp = fopen(path, "w");

    fprintf("%f %f | ", data->nbLines, data->nbColumns);

    for(int i = 0; i < data->nbLines; i++){
        for(int j = 0; j < data->nbColumns; j++){
            fprintf(fp, "%f", data->data[i][j]);
            if(j < data->nbColumns-1)
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
}
