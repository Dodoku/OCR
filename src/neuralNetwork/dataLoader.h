#ifndef DATA_LOADER_H
#define DATA_LOADER_H

typedef struct {

    int nbColumns;
    int nbLines;

    double **data;
} Data;

Data load_data(char *path);
void save_data(Data *data, char *path);

#endif
