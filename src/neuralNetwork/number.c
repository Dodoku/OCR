#include <stdlib.h>
#include <string.h>

#include "neuralNetwork.h"
#include "../tools/image.h"
#include "number.h"
#include "dataLoader.h"

#define assets_folder "tests/network/numbers"

#define nbHiddens 1
#define nbNeurons 15

#define imageSize 28

#define validCount 100
#define timeOutCount 250

Network init_number(){
    return init_network(imageSize*imageSize, nbHiddens, nbNeurons, 10);
}

void train_number(Network *net, char* dataset_path){
    
    int count = 0;
    int valid = 0;

    while (valid < validCount && count <= timeOutCount){
        printf("%i/%i\n", count, timeOutCount);
        FILE *fp = open_train(dataset_path);

        while(valid < validCount){
            TrainData data = read_train_image(fp);

            if(data.expectedNumber < 0)
                break;

            for(int y = 0; y < imageSize; y++){
                for(int x = 0; x < imageSize; x++){
                    SDL_Color color = get_pixel(data.image, x, y);
                    if(color.r > 255/2){
                        net->input.neurons[y*imageSize+x].value = 1.0;
                    }else{
                        net->input.neurons[y*imageSize+x].value = 0.0;
                    }
                }
            }

            forward_prop(net);

            int max = 0;
            double exp[10];
            for(int k = 0; k < 10; k++){
                if(net->output.neurons[k].value > 
                                net->output.neurons[max].value){
                    max = k; 
                }
                if(k == data.expectedNumber){
                    exp[k] = 1.0;
                }else {
                    exp[k] = 0.0;
                }
            }
            if(max == data.expectedNumber)
                valid++;
            else
                valid = 0;

            back_prop(net, exp, 1);

            SDL_FreeSurface(data.image);
            
        }
        count++;
        fclose(fp);
    }
    if(count == timeOutCount){
        printf("timeout...\n");
    }
}

int eval_number(Network *net, SDL_Surface *image){
    for(int y = 0; y < imageSize; y++){
        for(int x = 0; x < imageSize; x++){
            SDL_Color color = get_pixel(image, x, y);
            if(color.r > 255/2){
                net->input.neurons[y*imageSize+x].value = 1.0;
            }else{
                net->input.neurons[y*imageSize+x].value = 0.0;
            }
        }
    }
    forward_prop(net);
    int max = 0;
    for(int k = 0; k < 10; k++){
        if(net->output.neurons[k].value > net->output.neurons[max].value)
            max = k;
        //printf("%i: %f\n", k, net->output.neurons[k].value);
    }
    //printf("\n");
    return max;
}
