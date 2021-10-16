#include <stdlib.h>
#include <math.h>

#include "neuralNetwork.h"

double rand_num(double start, double end);

/*
 * Initialization
 */

static void init_neuron(Neuron *neuron, int nbPrevNeurons){
    neuron->nbWeights = nbPrevNeurons;
    if(nbPrevNeurons > 0)
        neuron->weights = (double*) malloc(nbPrevNeurons * 
                                        sizeof(*neuron->weights));

    neuron->biais = rand_num(-1, 1);
    neuron->value = 0;

    for(int i = 0; i < nbPrevNeurons; i++)
        neuron->weights[i] = rand_num(-1, 1);
}

static void init_layer(Layer *layer, int nbNeurons, int nbPrevNeurons){
    layer->nbNeurons = nbNeurons;
    layer->neurons = (Neuron*) malloc(nbNeurons * 
                                        sizeof(*layer->neurons));

    for(int i = 0; i < nbNeurons; i++)
        init_neuron(&layer->neurons[i], nbPrevNeurons);
}

Network init_network(int nbInputs, int nbLayers, int nbHiddens, int nbOutputs){ 
    Network net;

    init_layer(&net.input, nbInputs, 0);

    net.nbHiddens = nbLayers;
    net.hiddens = (Layer*) malloc(nbLayers * sizeof(*net.hiddens));
    for(int i = 0; i < nbLayers; i++)
        init_layer(&net.hiddens[i], nbHiddens, 
                    i > 0 ? nbHiddens : nbInputs);

    init_layer(&net.output, nbOutputs, nbHiddens);
    return net;
}

/*
 * Free
 */

static void free_neuron(Neuron *neuron){
    if(neuron->nbWeights > 0)
        free(neuron->weights);
}

static void free_layer(Layer *layer){
    for(int i = 0; i < layer->nbNeurons; i++)
        free_neuron(&layer->neurons[i]);

    free(layer->neurons);
}

void free_network(Network *net){
    free_layer(&net->input);
    
    for(int i = 0; i < net->nbHiddens; i++)
        free_layer(&net->hiddens[i]);
    free(net->hiddens);

    free_layer(&net->output);
}

/*
 * Propagation
 */

static Layer* get_layer(Network *net, int pos){
    if(pos < 0) return &net->input;
    if(pos >= net->nbHiddens) return &net->output;
    return &net->hiddens[pos];
}

void forward_prop(Network *net, double *inputs){
    for(int i = 0; i < net->input.nbNeurons; i++)
        net->input.neurons[i].value = inputs[i];
    
    for(int i = 0; i <= net->nbHiddens; i++){
        Layer *layer = get_layer(net, i);
        Layer *prev = get_layer(net, i-1);
        
        for(int j = 0; j < layer->nbNeurons; j++){
            Neuron *neu = &layer->neurons[j];
            
            double result = neu->biais;
            for(int k = 0; k < prev->nbNeurons; k++){
                result += prev->neurons[k].value * neu->weights[k];
            }

            neu->value = sigmoid(result);
        }
    }
}

/*
 * Tools
 */

double rand_num(double start, double end){
    return (end-start)*((double)random()/RAND_MAX)+start;
}
double sigmoid(double x){
    return 1.0/(exp(-x)+1.0);
}

double sigmoidPrime(double x){
    return x*(1.0-x);
}
