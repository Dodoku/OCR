#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNetwork.h"
#include "../tools/image.h"
#include "dataLoader.h"

#include "xor.h"
#include "number.h"

#define assets_folder "tests/network/numbers"
/**
 * ./neuronNetwork (path)
 */

int main(int argc, char *argv[]){
    srand( time( NULL ) );

    Network net;

    net = load_network("record_numbers.data");

    //train_number(&net, "train.data");

    //net = 

    for(int i = 0; i < 10; i++){
        char str[40] = "tests/network/numbers_v2/";
        char num = i + '0';
        strncat(str, &num, 1);
        strcat(str, ".jpg");
        SDL_Surface *image = load(str);
        int result = eval_number(&net, image);
        printf("%s => %i\n", str, result);
        SDL_FreeSurface(image);
    }

    //save_network(&net, "record_numbers.data");

    /*for(int i = 0; i <= 9; i++){
            char path[1024] = "";
            strcat(path, assets_folder);
            strcat(path, "/");
            strcat(path, (char[2]) { (char) i + '0', '\0' });
            strcat(path, ".jpg");

            SDL_Surface *image = load(path);
            int result = eval_number(&net, image);
            printf("Input image %i.jpg : result is %i\n", i, result);
    }*/

    /*if(argc >= 2){
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
    }*/

    free_network(&net);
    return EXIT_SUCCESS;
}
