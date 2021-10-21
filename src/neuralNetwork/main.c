#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNetwork.h"
#include "dataLoader.h"
#include "xor.h"


/**
 * ./neuronNetwork
 */


int main(int argc, char *argv[]){
    srand( time( NULL ) );

    Network net;

    if(argc >= 2){
        printf("Loading Network WITH Data file...\n");
        net = load_network(args[0]);
        printf("Loading Data finished");
    }else {
        net = init_xor();
        printf("Loading Network WITHOUT Data file...\n");
        printf("Learning Network with XOR responses...\n");
        int count = train_xor(&net);
        printf("Learning XOR finished (with %i iterations)\n", count);
    }


    printf("Network is ready !\n");
    printf("---------------------\n\n");

    while (1){

        for(int i = 0; i < net->input.nbNeurons; i++){
            printf("Input[%i] = ", i);
            double d;
            scanf("%lf", &d);
            net->input.neurons[i].value = d;
        }

        printf("\n");
        forwo



    }




    double inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};


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
