#include <stdio.h>
#include <math.h>

#include "neuralNetwork.h"

#define nbHiddens 1
#define nbNeurons 4

#define validCount 1000

Network init_xor(){
    return init_network(2, nbHiddens, nbNeurons, 1);
}

int train_xor(Network *net){
    double inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    double exp[4][1] =    { {0},   {1},   {1},   {0} };

    int count = 0;
    int valid = 0;

    while(valid < validCount && count < 100000){
            for(int i = 0; i < 4; i++){
                forward_prop(net, inputs[i]);

                if(exp[i][0] == 1 && net->output.neurons[0].value > 0.95)
                    valid++;
                else if(exp[i][0] == 0 && net->output.neurons[0].value < 0.05)
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
    double inputs[2] = {a, b};
    forward_prop(net, inputs);
    return net->output.neurons[0].value;
}
