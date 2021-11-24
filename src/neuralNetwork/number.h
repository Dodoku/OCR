#ifndef NUMBER_H
#define NUMBER_H

#include <SDL2/SDL_image.h>

Network init_number();
void train_number(Network *net);

int eval_number(Network *net, SDL_Surface *image);

#endif
