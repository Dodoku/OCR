#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct gui_data {
    GtkBuilder *builder;
    SDL_Surface *loadImage;

    SDL_Surface *editedImage;
    SDL_Surface *rotateImage;

    int minX;
    int minY;

    int maxX;
    int maxY;

    GtkButton *pressed;
    guint event;

    pthread_t thread;

    GtkWindow *mainWindow;
};

struct filter_data {
    int grayscale;

    int blur;
    int otsu;
};

void error_message(char *message);
void info_message(char *message);

GtkBuilder *init_gui();


#endif