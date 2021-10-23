#include <stdio.h>
#include <math.h>

#include "neuralNetwork.h"
#include "xor.h"

#define nbHiddens 1
#define nbNeurons 6

#define validCount 100

Network init_xor(){
    return init_network(2, nbHiddens, nbNeurons, 1);
}

void print_xor(Network *net){
    double inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};

    for(int i = 0; i < 4; i++){
        printf("\nInput[0] = %f\nInput[1] = %f\n---\n", 
                                inputs[i][0], inputs[i][1]);
        eval_xor(net, inputs[i][0], inputs[i][1]);
        printf("Output[0] = %f\n", net->output.neurons[0].value); 
    }
}

int train_xor(Network *net){
    double inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    double exp[4][1] =    { {0},   {1},   {1},   {0} };

    int count = 0;
    int valid = 0;

    while(valid < validCount && count < 10000){
            for(int i = 0; i < 4; i++){
                double out = eval_xor(net, inputs[i][0], inputs[i][1]);

                if(exp[i][0] == 1 && out > 0.95)
                    valid++;
                else if(exp[i][0] == 0 && out < 0.05)
                    valid++;
                else
                    valid = 0;
                back_prop(net, exp[i], 1);
            }
        count++;
    }

    return count;
}

double eval_xor(Network *net, double a, double b){
    net->input.neurons[0].value = a;
    net->input.neurons[1].value = b;
    forward_prop(net);
    return net->output.neurons[0].value;
}
