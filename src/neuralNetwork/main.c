#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNetwork.h"
#include "dataLoader.h"
#include "xor.h"

int main(int argc, char *argv[]){
    srand( time( NULL ) );

    if(argc <= 2){
        printf("Usage: ./neuralNetwork <load/train> <path>")
    }

    Network net;

    if(argv[1] == "load"){
        printf("Loading Network with Data file...\n");
        net = load_network(args[2]);
        printf("Loading Finished\n");
    }else if(argv[1] == "train"){
        printf("Starting the training of network...\n");
        net = train_xor();
        printf("Train Finished\n");
    }


    double inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};

    Network net = init_xor();
    int count = train_xor(&net);
    printf("Train efficent : %i", count);

    save_network(&net, "tests/network/record_xor.data");

    /*Network net = init_network(2, 1, 4, 1);
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
    }*/


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
