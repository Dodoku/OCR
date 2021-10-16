#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

typedef struct {

    int nbWeights;

    double *weights;
    //double biais; #not useful

    double value;

} Neuron;

typedef struct {

    int nbNeurons;
    Neuron *neurons;

} Layer;

typedef struct {
    
    int nbHiddens;

    Layer input;
    Layer *hiddens;
    Layer output;

} Network;

Network init_network(int nbInputs, int nbLayers, int nbHiddens, int nbOutputs);
void free_network(Network *net);

void forward_prop(Network *net, double *inputs);
void back_prop(Network *net, double *expOutput, double ratio);

double sigmoid(double x);
double sigmoidPrime(double x);

#endif
