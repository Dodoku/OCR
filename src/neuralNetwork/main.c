#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNetwork.h"
#include "dataLoader.h"
#include "../tools/image.h"

#include "xor.h"
#include "number.h"


/**
 * ./neuronNetwork
 */


int main (int argc, char *argv[]){
    srand( time( NULL ) );

    Network net;

    net = init_number();
    
    train_number(&net);

    int nb = eval_number(&net, load("tests/network/numbers/4.jpg"));
    printf("%i\n", nb);

    double exp[10];
    for(int k = 0; k < 10; k++){
        if(k == 4){
            exp[k] = 1.0;
        }else {
            exp[k] = 0.0;
        }
    }

    back_prop(&net, exp, 1);

    nb = eval_number(&net, load("tests/network/numbers/5.jpg"));
    printf("%i\n", nb);

    nb = eval_number(&net, load("tests/network/numbers/6.jpg"));
    printf("%i\n", nb);
}

/*int main(int argc, char *argv[]){
    srand( time( NULL ) );

    Network net;

    if(argc >= 2){
        printf("Loading Network WITH Data file...\n");
        net = load_network(argv[1]);
        printf("Loading Data finished\n");
    }else {
        net = init_xor();
        printf("Loading Network WITHOUT Data file...\n");
        printf("Learning Network with XOR responses...\n");
        int count = train_xor(&net);
        printf("Learning XOR finished (with %i iterations)\n", count);
    }


    printf("Network is ready!\n");
    printf("---------------------\n\n");
    print_xor(&net);
    printf("---------------------\n\n");

    while (1){
        double d1;
        double d2;

        printf("Input[0] = ");
        scanf("%lf", &d1);

        printf("Input[1] = ");
        scanf("%lf", &d2);

        printf("\n");
        double out = eval_xor(&net, d1, d2);

        printf("Output[0] = %lf\n", out);

        printf("Do you want to try again? (y/n) ");
        char c[1] = "";
        scanf("%s", c);
        if(c[0] == 'n'){
            break;
        }
        printf("\n");
    }

    if(argc < 2){
        printf("Do you want to save network Data? (y/n) ");
        char c[1] = "";
        scanf("%s", c);
        if(c[0] == 'y'){
            printf("Path to save file : ");
            char path[2048] = "";
            scanf("%s", path);
            save_network(&net, path);
            printf("File saved successfully in %s\n", path);
        }
    }

    free_network(&net);
    return EXIT_SUCCESS;
}*/
