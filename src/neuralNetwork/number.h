#ifndef NUMBER_H
#define NUMBER_H

Network init_number();
void train_number(Network *net);

int eval_number(Network *net, SDL_Surface *image);

#endif
