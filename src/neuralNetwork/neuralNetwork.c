#include "neuralNetwork.h"

Network init_network(int nbInputs, int nbHidden, int nbOutput) {
    
    Network net;

    net.nbInputs = nbInputs;
    net.nbHidden = nbHidden;
    net.nbOutput = nbOutput;

    net.nbWeights = nbHidden * (nbInputs + nbOutput);

}
