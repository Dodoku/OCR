#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNetwork.h"
#include "dataLoader.h"

void print_net(Network *net){
    for(int i = 0; i < net->nbHiddens; i++){
        for(int j = 0; j < net->hiddens[i].nbNeurons; j++){
            for(int k = 0; k < net->hiddens[i].neurons[j].nbWeights; k++){
                printf("%f ", net->hiddens[i].neurons[j].weights[k]);
            }
            printf("\n");
        }
        printf("----");
    }
}

int main(){
    srand( time( NULL ) );
    
    Network net = init_network(2, 1, 4, 1);
    double inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    double **ip = malloc(4 * sizeof(double));
    for (int i = 0; i < 4; i++){
        ip[i] = malloc(2 * sizeof(double));
        for(int j = 0; j < 2; j++)
            ip[i][j] = inputs[i][j];
    }
    
    double exp[4][1] = {{0},{1},{1},{0}};
    printf("Init\n");
    for(int h = 0; h < 1000; h++){
        for(int i = 0; i < 4; i++){
            forward_prop(&net, inputs[i]);
            back_prop(&net, exp[i], 1);
        }
    }


    printf("Learn Finish\n");
    save_network(&net, "tests/network/record_xor.data");

    print_net(&net);
    printf("-------------\n");
    for(int i = 0; i < 4; i++){
        printf("\nInput[0] = %f\nInput[1] = %f\n---\n", 
                                inputs[i][0], inputs[i][1]);
        forward_prop(&net, inputs[i]);
        printf("Output[0] = %f\n", net.output.neurons[0].value); 
    }
    printf("Finished\n");

    free_network(&net);
    return EXIT_SUCCESS;
}
