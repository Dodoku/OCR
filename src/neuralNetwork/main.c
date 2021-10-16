#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNetwork.h"

int main(){
    srand( time( NULL ) );

    Network net = init_network(2, 2, 5, 1);
    double inputs[2] = {10, 1};
    printf("Init\n");
    forward_prop(&net, inputs);
    for(int i = 0; i < net.output.nbNeurons; i++)
        printf("Output [%i] :  %f\n", i, net.output.neurons[i].value);
    free_network(&net);
    printf("Finished\n");
    return EXIT_SUCCESS;
}
