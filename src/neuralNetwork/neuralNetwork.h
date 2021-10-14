typedef struct {
    // To Compute
    int nbWeights; // <= number of weights in the network
    int nbBiais;   // <= number of biais in the network

    // Values in arrays
    float *weights; // <= array of all weights
    float *biais;   // <= array of all biais

    // Neurones
    int nbInputs; // <= number of input neurons
    int nbHidden; // <= total number of hidden neurons
    int nbOutput; // <= number of output neurons

    float *inputs; // <= array of all inputs neurons
    float *hidden; // <= array of all hidden neurons
    float *output; // <= array of all output neurons
} Network;
