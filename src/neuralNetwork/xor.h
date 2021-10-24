#ifndef XOR_H
#define XOR_H

Network init_xor();
void print_xor(Network *net);

int train_xor(Network *net);
double eval_xor(Network *net, double a, double b);

#endif
