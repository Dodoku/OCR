#ifndef NUMBER_H
#define NUMBER_H

#include <gtk/gtk.h>
#include <SDL2/SDL_image.h>

Network init_number();

void train_number_with_gui(Network *net, char* dataset_path, int loop,
                                GtkLabel *error_rate, GtkLabel* trainings_loop);
void train_number(Network *net, char* dataset_path);

int eval_number(Network *net, SDL_Surface *image);

#endif
