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
    SDL_Surface *slipImage;
    SDL_Surface *withoutEdgeMap;
    SDL_Surface *generatedImage;

    int x1, y1, x2, y2;
    char *output;

    GtkButton *pressed;
    guint event;

    int inThread;
    pthread_t thread;

    GtkWindow *mainWindow;
};

struct filter_data {
    int grayscale;

    int blur;
    int otsu;
    int edgeMap;

    int isAuto;
};

void error_message(char *message);
void info_message(char *message);

void split_update();
void filter_update();
void rotate_update();

GtkBuilder *init_gui();


#endif
