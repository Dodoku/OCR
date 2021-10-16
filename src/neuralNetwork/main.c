#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNetwork.h"

int main(){
    srand( time( NULL ) );

    Network net = init_network(2, 1, 6, 1);
    double inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    double exp[4][1] = {{0},{1},{1},{0}};
    printf("Init\n");
    for(int h = 0; h < 1000; h++){
        for(int i = 0; i < 4; i++){
            forward_prop(&net, inputs[i]);
            printf("Erreur [%i] : %f\n", i, exp[i][0]-
                                            net.output.neurons[i].value);
            for(int i = 0; i < net.output.nbNeurons; i++)
                printf("Output [%i] :  %f\n\n", i, net.output.neurons[i].value);
            back_prop(&net, exp[i], 1);
        }
    }


    printf("Learn Finish\n");
    printf("-------------\n");
    for(int i = 0; i < 4; i++){
        printf("\nInput[0] = %f\nInput[1] = %f\n---\n", 
                                inputs[i][0], inputs[i][1]);
        forward_prop(&net, inputs[i]);
        printf("Output[0] = %f\n", net.output.neurons[0].value); 
    }
    printf("Finished\n");
    return EXIT_SUCCESS;
}
