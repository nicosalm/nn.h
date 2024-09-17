
#if !defined(NN_H)
#define NN_H

#include <stdint.h>
#include <math.h>   // exp(), tanh(), etc.
#include <stdlib.h>

typedef double (*activation_func)(double);
typedef double (*random_func)();
typedef double (*weight_init_func)(uint32_t n_in, uint32_t n_out);

typedef struct Network {
    double* weights_hidden;
    double* biases_hidden;
    double* weights_output;
    double* biases_output;
    double* hidden_layer;
    double* output_layer;
    uint32_t n_inputs;
    uint32_t n_hidden;
    uint32_t n_outputs;
    activation_func activation_hidden;
    activation_func activation_output;
    weight_init_func weight_init;
} Network;

typedef struct Trainer {
    double* gradients_hidden;
    double* gradients_output;
} Trainer;

Network* network_init(Network* network,
                      uint32_t n_inputs,
                      uint32_t n_hidden,
                      uint32_t n_outputs,
                      random_func rand_func,
                      activation_func hidden_activation,
                      activation_func output_activation,
                      weight_init_func weight_initializer);

void network_free(Network* network);
void network_predict(Network* network, double* input);

Trainer* trainer_init(Trainer* trainer, Network* network);
void trainer_train(Trainer* trainer, Network* network, double* input, double* output, double learning_rate);
void trainer_free(Trainer* trainer);

double relu(double x);
double sigmoid(double x);
double tanh_activation(double x);

double random_init(uint32_t n_in, uint32_t n_out);
double xavier_init(uint32_t n_in, uint32_t n_out);
double he_init(uint32_t n_in, uint32_t n_out);

#endif

