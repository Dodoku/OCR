#include <string.h>

#include "neuralNetwork.h"
#include "../tools/image.h"
#include "number.h"

#define assets_folder "tests/network/numbers"

#define nbHiddens 1
#define nbNeurons 15

#define imageSize 28

#define validCount 10

Network init_number(){
    return init_network(imageSize*imageSize, nbHiddens, nbNeurons, 10);
}

void train_number(Network *net){
    
    int count = 0;
    int valid = 0;

    while(valid < validCount && count < 1000){
        for(int i = 0; i <= 9; i++){
            char path[1024] = "";
            strcat(path, assets_folder);
            strcat(path, "/");
            strcat(path, (char[2]) { ((char) i) + '0', '\0' });
            strcat(path, ".jpg");

            SDL_Surface *image = load(path);

            for(int y = 0; y < imageSize; y++){
                for(int x = 0; x < imageSize; x++){
                    SDL_Color color = get_pixel(image, x, y);
                    if(color.r < 255/2){
                        net->input.neurons[y*9+x].value = 1.0;
                    }else{
                        net->input.neurons[y*9+x].value = 0.0;
                    }
                }
            }

            forward_prop(net);
            double exp[10];
            for(int k = 0; k < 10; k++){
                if(k == i){
                    exp[k] = 1.0;
                }else {
                    exp[k] = 0.0;
                }
            }

            back_prop(net, exp, 1);
        }
        count++;
    }

}

int eval_number(Network *net, SDL_Surface *image){
    for(int y = 0; y < imageSize; y++){
        for(int x = 0; x < imageSize; x++){
            SDL_Color color = get_pixel(image, x, y);
            if(color.r < 255/2){
                net->input.neurons[y*9+x].value = 1.0;
            }else{
                net->input.neurons[y*9+x].value = 0.0;
            }
        }
    }
    forward_prop(net);
    int max = 0;
    for(int k = 1; k < 10; k++){
        if(net->output.neurons[k].value > net->output.neurons[max].value)
            max = k;
    }
    return max;
}
