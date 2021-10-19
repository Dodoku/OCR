#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "neuralNetwork.h"
#include "dataLoader.h"


Data init_data(int nbLines, int nbColumns){
    Data data;

    data.nbLines = nbLines;
    data.nbColumns = nbColumns;

    data.data = malloc(data.nbLines * sizeof(*data.data));

    for(int i = 0; i < data.nbLines; i++)
        data.data[i] = malloc(data.nbColumns * sizeof(**data.data));

    return data;
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

    fscanf(fp, "%i %i |", &data.nbLines, &data.nbColumns);
    data = init_data(data.nbLines, data.nbColumns);

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

    fprintf(fp, "%i %i | ", data->nbLines, data->nbColumns);

    for(int i = 0; i < data->nbLines; i++){
        for(int j = 0; j < data->nbColumns; j++){
            if(data->data[i][j] != 0){
                fprintf(fp, "%f", data->data[i][j]);
                if(j < data->nbColumns-1)
                    fprintf(fp, " ");
            }
        }
        if(i < data->nbLines-1)
            fprintf(fp, "\n");
    }
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

    Data data = init_data(2 + net->nbHiddens * net->hiddens[0].nbNeurons, max);
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