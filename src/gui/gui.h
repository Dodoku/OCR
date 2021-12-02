#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct gui_data {
    GtkBuilder *builder;
    SDL_Surface *loadImage;

    SDL_Surface *editedImage;

    pthread_t thread;
};

void error_message(char *message);
void info_message(char *message);

GtkBuilder *init_gui();


#endif