#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

#include "neuralNetwork.h"
#include "dataLoader.h"
#include "../tools/image.h"

Data init_data(int nbLines, int nbColumns){
    Data data;

    data.nbLines = nbLines;
    data.nbColumns = nbColumns;

    data.data = malloc(data.nbLines * sizeof(*data.data));

    for(int i = 0; i < data.nbLines; i++){
        data.data[i] = malloc(data.nbColumns * sizeof(**data.data));
    }

    for(int i = 0; i < data.nbLines; i++)
        for(int j = 0; j < data.nbColumns; j++)
            data.data[i][j] = 0;
        
    return data;
}

void print_data(Data *data){
    for(int i = 0; i < data->nbLines; i++){
        for(int j = 0; j < data->nbColumns; j++){
            printf("%f ", data->data[i][j]);
        }
        printf("\n");
    }
}

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

    double a[4];

    fscanf(fp, "%i %i | %lf %lf %lf %lf", &data.nbLines, &data.nbColumns, 
            &a[0], &a[1], &a[2], &a[3]);
    data = init_data(data.nbLines, data.nbColumns);

    for (int i = 0; i < 4; i++)
        data.data[0][i] = a[i];

    while(!feof(fp)){
        if (getline(&c, &n, fp) > 1){
            char *strToken = strtok (c," ");
            while (strToken != NULL && strToken[0] != '\n' 
                                        && strToken[0] != '\0'){
                data.data[line][column] = atof(strToken);
                column++;
                strToken = strtok (NULL, " ");
            }
            line++;
            column = 0;
        }
    }

    fclose(fp);
    return data;
}

void save_data(Data *data, char *path){
    FILE *fp;

    fp = fopen(path, "w");

    fprintf(fp, "%i %i | ", data->nbLines, data->nbColumns);

    for(int i = 0; i < data->nbLines; i++){
        for(int j = 0; j < data->nbColumns; j++){
            if(data->data[i][j] != 0){
                fprintf(fp, "%f", data->data[i][j]);
                if(j < data->nbColumns-1)
                    fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void free_data(Data *data){
    for(int i = 0; i < data->nbLines; i++)
        free(data->data[i]);

    free(data->data);
}

Network load_network(char *path){
    Data data = load_data(path);
    Network net = init_network((int)data.data[0][0], (int)data.data[0][1], 
                                (int)data.data[0][2], (int)data.data[0][3]);
    int line = 1;
    for(int i = 0; i <= net.nbHiddens; i++){
        Layer *layer = get_layer(&net, i);
        for(int j = 0; j < layer->nbNeurons; j++){
            for(int k = 0; k < layer->neurons[j].nbWeights; k++){
                layer->neurons[j].weights[k] = data.data[line][k];
            }
            line++;
        }
    }

    free_data(&data);
    return net;
}

void save_network(Network *net, char *path){
    int max = 4;
    if(max < net->hiddens[0].nbNeurons)
        max = net->hiddens[0].nbNeurons;
    if(max < net->input.nbNeurons)
        max = net->input.nbNeurons;
    if(max < net->output.nbNeurons)
        max = net->output.nbNeurons;

    Data data = init_data(1 + net->output.nbNeurons + net->hiddens[0].nbNeurons
                                     * net->nbHiddens, max);
    data.data[0][0] = net->input.nbNeurons;
    data.data[0][1] = net->nbHiddens;
    data.data[0][2] = net->hiddens[0].nbNeurons;
    data.data[0][3] = net->output.nbNeurons;

    int line = 1;
    for(int i = 0; i <= net->nbHiddens; i++){
        Layer *layer = get_layer(net, i);
        for(int j = 0; j < layer->nbNeurons; j++){
            for(int k = 0; k < layer->neurons[j].nbWeights; k++){
                data.data[line][k] = layer->neurons[j].weights[k];
            }
            line++;
        }
    }

    save_data(&data, path);
    free_data(&data);
}

FILE *open_train(char *path){
    FILE *fp;

    fp = fopen(path, "r");
    if (!fp)
        errx(1, "Couldn't open %s\n", path);

    return fp;
}


TrainData read_train_image(FILE *file){
    TrainData data;

    data.expectedNumber = -1;

    char c;
    int readImage = 0;

    SDL_Surface *image = create_empty(28, 28);
    size_t x = 0;

    while((c = fgetc(file)) != EOF){
        if(c == '\n')
            break;
        if(c >= '0' && c <= '9' && x < 28*28){
            if(readImage){
                set_pixel(image, x%28, x/28, (c - '0') == 0 ? to_color(0, 0, 0, 255)
                                                : to_color(255, 255, 255, 255));
                x++;
            }else{
                data.expectedNumber = c - '0';
                readImage = 1;  
            }
        }
    }

    if(data.expectedNumber == -1)
        SDL_FreeSurface(image);
    else
        data.image = image;

    return data;
}

int countLines(FILE *fp){

    int lines = 0;
    
    while(!feof(fp)){
        if(getc(fp) == '\n')
            lines++;
    }

    fclose(fp);
    return lines;
}