#include <string.h>

#include "neuralNetwork.h"
#include "../tools/image.h"

#define assets_folder tests/network/numbers

#define nbHiddens 2
#define nbNeurons 6

Network init_number(){
    return init_network(32*32, nbHiddens, nbNeurons, 10);
}

void train_number(Network *net){

    for(int i = 1; i <= 9; i++){
        char path[1024];
        strcpy(path, assets_folder);
        strcpy(path, "/");
        strcpy(path, i + '0');
        strcpy(path, ".jpg");

        SDL_Surface *image = load(path);

        for(int x = 0; x < 32; x++){
            for(int y = 0; y < 32; y++){
                SDL_Color color = get_pixel(image, x, y);
                if(color.r < 255/2){
                    net->input.neurons[x*9+y] = 1.0;
                }else{
                    net->input.meurons[x*9+y] = 0.0;
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

        backward_prop(net, exp);
    }
}
