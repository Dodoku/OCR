#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#include "gui.h"
#include "../tools/image.h"
#include "train_gui.h"

#include "../imageProcess/rotate.h"
#include "../imageProcess/rotate.h"
#include "../imageProcess/contrast.h"
#include "../imageProcess/grayscale.h"
#include "../imageProcess/noise_reduction.h"
#include "../imageProcess/canny.h"

#include "../tools/hough.h"

void error_message(char *message)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                        GTK_BUTTONS_OK, message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void info_message(char *message){
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                        GTK_BUTTONS_OK, message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

GdkPixbuf *gtk_image_new_from_sdl_surface (SDL_Surface *surface)
{
    Uint32 src_format;
    Uint32 dst_format;

    GdkPixbuf *pixbuf;
    gboolean has_alpha;
    int rowstride;
    guchar *pixels;

    // select format                                                            
    src_format = surface->format->format;
    has_alpha = SDL_ISPIXELFORMAT_ALPHA(src_format);
    if (has_alpha) {
        dst_format = SDL_PIXELFORMAT_RGBA32;
    }
    else {
        dst_format = SDL_PIXELFORMAT_RGB24;
    }

    // create pixbuf                                                            
    pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, has_alpha, 8,
                             surface->w, surface->h);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    pixels = gdk_pixbuf_get_pixels (pixbuf);

    // copy pixels                            
    SDL_LockSurface(surface);
    SDL_ConvertPixels (surface->w, surface->h, src_format,
               surface->pixels, surface->pitch,
               dst_format, pixels, rowstride);
    SDL_UnlockSurface(surface);

    return pixbuf;
}

struct gui_data *data;

//------------------------------------------------------------------------------
// THREADS
//------------------------------------------------------------------------------

static void* refresh_image_split(){
    GtkImage *image = GTK_IMAGE(gtk_builder_get_object(data->builder, "splitting_image"));

    GtkSwitch *grayscaleToggle = GTK_SWITCH(gtk_builder_get_object(data->builder, 
                                                        "grayscale_switch"));
    if(!gtk_switch_get_active(grayscaleToggle)){
        gtk_image_set_from_file(image, NULL);
        data->inThread = 0;
        return NULL;
    }

    if(data->slipImage != NULL)
        SDL_FreeSurface(data->slipImage);

    data->slipImage = copy(data->rotateImage);
    //hough_transform(data->slipImage);

    GdkPixbuf *pixbuf = gtk_image_new_from_sdl_surface(data->slipImage);
    int width = gdk_pixbuf_get_width (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    width = (double)width * ((double)500/height);
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, 500, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(image, pixbuf);
    data->inThread = 0;
    return NULL;
}

static void* refresh_image_filter(void * p_data){
    struct filter_data *fdata = (struct filter_data*)p_data;
    GtkImage* filterImage = GTK_IMAGE(gtk_builder_get_object(data->builder, 
                                                            "filter_image"));

    /*GtkWidget* apply_filter = GTK_WIDGET(gtk_builder_get_object(data->builder, 
                                                            "apply_filter"));*/

    if(data->editedImage != NULL)
        SDL_FreeSurface(data->editedImage);

    data->editedImage = copy(data->loadImage);
    if(fdata->grayscale)
        data->editedImage = to_grayscale(data->editedImage);
    if(fdata->blur)
        data->editedImage = simple_blur(data->editedImage, fdata->blur);
    if(fdata->otsu)
        data->editedImage = otsu(data->editedImage, fdata->otsu);
    data->withoutEdgeMap = copy(data->editedImage);
    if(fdata->edgeMap)
        data->editedImage = edgemap(data->editedImage);

    if(fdata->isAuto && !test_proportions(data->editedImage) && fdata->otsu < 50){
        fdata->blur += 1;
        fdata->otsu += 15;
        GtkSpinButton *blurSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(data->builder, 
                                                        "nbblur"));
        GtkSpinButton *ostuSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(data->builder, 
                                                        "nbotsu"));
        gtk_spin_button_set_value(blurSpin, fdata->blur);
        gtk_spin_button_set_value(ostuSpin, fdata->otsu);
        refresh_image_filter(fdata);
        return NULL;
    }
    GdkPixbuf *pixbuf = gtk_image_new_from_sdl_surface(data->editedImage);
    int width = gdk_pixbuf_get_width (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    width = (double)width * ((double)450/height);
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, 450, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filterImage, pixbuf);
    free(fdata);
    data->inThread = 0;
    rotate_update();
    return NULL;
}

static void* refresh_image_rotate(void * p_data){
    int angle = *((int*)p_data);
    free((int*)p_data);
    GtkImage* rotateImage = GTK_IMAGE(gtk_builder_get_object(data->builder, 
                                                            "rotate_image"));

    if(data->rotateImage != NULL)
       SDL_FreeSurface(data->rotateImage);
    data->rotateImage = copy(data->editedImage);
    if(angle >= -180 && angle <= 180)
        data->rotateImage = rotate(data->rotateImage, angle*M_PI/180);
    GdkPixbuf *pixbuf = gtk_image_new_from_sdl_surface(data->rotateImage);

    int width = gdk_pixbuf_get_width (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    width = (double)width * ((double)500/height);
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, 500, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(rotateImage, pixbuf);
    data->inThread = 0;
    return NULL;
}

gboolean loopRefreshSensitive(){
    GtkWidget* confirmButton = GTK_WIDGET(gtk_builder_get_object(data->builder, 
                                                            "confirmbutton"));
    GtkWidget* stack = GTK_WIDGET(gtk_builder_get_object(data->builder, 
                                                            "stack1"));
    gtk_widget_set_sensitive(confirmButton, !data->inThread);
    gtk_widget_set_sensitive(stack, !data->inThread);
    return TRUE;
}

//------------------------------------------------------------------------------
// EVENTS
//------------------------------------------------------------------------------

void split_update(){
    if(data->inThread)
        pthread_exit(&data->thread);
    data->inThread = 1;
    pthread_create(&data->thread, NULL, refresh_image_split, NULL);
}

void filter_auto(){
    struct filter_data *fdata = malloc(sizeof(struct filter_data));
    GtkSwitch *grayscaleToggle = GTK_SWITCH(gtk_builder_get_object(data->builder, 
                                                            "grayscale_switch"));
    GtkSpinButton *blurSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(data->builder, 
                                                            "nbblur"));
    GtkSpinButton *ostuSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(data->builder, 
                                                            "nbotsu"));
    GtkSwitch *edgeMapToggle = GTK_SWITCH(gtk_builder_get_object(data->builder, 
                                                            "edgeMap_switch"));
    gtk_switch_set_active(grayscaleToggle, 1);
    gtk_spin_button_set_value(blurSpin, 0);
    gtk_spin_button_set_value(ostuSpin, 1);
    gtk_switch_set_active(edgeMapToggle, 1);
    
    fdata->grayscale = 1;
    fdata->blur = 0;
    fdata->otsu = 1;
    fdata->edgeMap = 1;
    fdata->isAuto = 1;

    if(data->inThread)
        pthread_exit(&data->thread);
    data->inThread = 1;
    pthread_create(&data->thread, NULL, refresh_image_filter, fdata);
}

void filter_update(){
    struct filter_data *fdata = malloc(sizeof(struct filter_data));
    GtkSwitch *grayscaleToggle = GTK_SWITCH(gtk_builder_get_object(data->builder, 
                                                            "grayscale_switch"));
    GtkSpinButton *blurSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(data->builder, 
                                                            "nbblur"));
    GtkSpinButton *ostuSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(data->builder, 
                                                            "nbotsu"));
    GtkSwitch *edgeMapToggle = GTK_SWITCH(gtk_builder_get_object(data->builder, 
                                                            "edgeMap_switch"));
                                                

    fdata->grayscale = gtk_switch_get_active(grayscaleToggle);
    fdata->blur = gtk_spin_button_get_value(blurSpin);
    fdata->otsu = gtk_spin_button_get_value(ostuSpin);
    fdata->edgeMap = gtk_switch_get_active(edgeMapToggle);
    fdata->isAuto = 0;

    if(data->inThread)
        pthread_exit(&data->thread);
    data->inThread = 1;
    pthread_create(&data->thread, NULL, refresh_image_filter, fdata);
}

void rotate_auto(){
    double angle = hough_transform(data->editedImage);
    printf("%f\n", angle);
    GtkRange *scale = GTK_RANGE(gtk_builder_get_object(data->builder, "rotation_slider"));
    gtk_range_set_value(scale, -angle*180/M_PI);
    rotate_update();
}

void rotate_update(){
    GtkRange *scale = GTK_RANGE(gtk_builder_get_object(data->builder, "rotation_slider"));
    int *angle = malloc(sizeof(int));
    *angle = gtk_range_get_value(scale);

    if(data->inThread){
        pthread_exit(&data->thread);
    }
    data->inThread = 1;
    pthread_create(&data->thread, NULL, refresh_image_rotate, angle);
}

void load_image(GtkFileChooserButton *button, gpointer user_data){
    struct gui_data *Data = user_data;

    if(Data->loadImage != NULL)
        SDL_FreeSurface(Data->loadImage);
    
    if(Data->editedImage != NULL)
        SDL_FreeSurface(Data->editedImage);

    if(Data->rotateImage != NULL)
        SDL_FreeSurface(Data->rotateImage);

    if(Data->slipImage != NULL)
        SDL_FreeSurface(Data->slipImage);
    
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
    Data->loadImage = load(filename);
    Data->editedImage = copy(Data->loadImage);
    Data->rotateImage = copy(Data->loadImage);
    Data->slipImage = copy(Data->loadImage);
    Data->withoutEdgeMap = copy(Data->loadImage);

    Data->minX = 0;
    Data->minY = 0;

    Data->maxX = Data->loadImage->w;
    Data->maxY = Data->loadImage->h;

    filter_update();
}

void open_fileChooser(){
    GtkWidget* openFile = GTK_WIDGET(gtk_builder_get_object(data->builder, 
                                                            "filename"));
    gtk_widget_show(openFile);
}

void open_AboutUs(){
    GtkWidget* openFile = GTK_WIDGET(gtk_builder_get_object(data->builder, 
                                                            "org.dodoku.about"));
    gtk_widget_show(openFile);
}

void close_AboutUs(){
    GtkWidget* openFile = GTK_WIDGET(gtk_builder_get_object(data->builder,
                                                            "org.dodoku.about"));
    gtk_widget_hide(openFile);
}

//------------------------------------------------------------------------------
// MAIN FUNCTION
//------------------------------------------------------------------------------

void menu_signals(GtkBuilder* builder){ 
    g_signal_connect(GTK_MENU_ITEM(gtk_builder_get_object(builder, "train_tools")), 
                                    "activate", G_CALLBACK(open_train_gui), builder);
    g_signal_connect(GTK_MENU_ITEM(gtk_builder_get_object(builder, "quit")), 
                                    "activate", G_CALLBACK(gtk_main_quit), builder);


    g_signal_connect(GTK_MENU_ITEM(gtk_builder_get_object(builder, "about-us")), 
                                    "activate", G_CALLBACK(open_AboutUs), builder);
    g_signal_connect(GTK_BUTTON(gtk_builder_get_object(builder, "close_about")), 
                                    "clicked", G_CALLBACK(close_AboutUs), builder);
}

GtkBuilder *init_gui(){
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Constructs a GtkBuilder instance.
    GtkBuilder* builder = gtk_builder_new ();

    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "res/dodoku.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return NULL;
    }
    
    data = malloc(sizeof(struct gui_data));
    data->builder = builder;
    data->loadImage = NULL;
    data->editedImage = NULL;
    data->rotateImage = NULL;
    data->slipImage = NULL;
    data->pressed = NULL;
    data->event = 0;
    data->inThread = 0;

    // Gets the widgets.
    GtkWindow* mainWindow = GTK_WINDOW(gtk_builder_get_object(builder, 
                                                            "org.dodoku.main"));
    GtkFileChooserButton* chooserButton = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, 
                                                            "filename"));
    GtkFileChooserButton* chooserNetworkButton = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, 
                                                            "network_data_file"));
    GtkButton* apply_rotate = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                            "apply_rotate"));
    GtkButton* auto_rotate = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                            "auto_rotate_button"));
    GtkButton* apply_filter = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                            "apply_filter"));
    GtkButton* auto_filter = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                            "auto_filter"));
    data->mainWindow = mainWindow;

    g_timeout_add(100, (GSourceFunc)loopRefreshSensitive, data);
    
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcat(cwd, "/res/record.data");
        gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(chooserNetworkButton), cwd);
    }

    // Connects event handlers.
    g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Buttons event handlers.
    g_signal_connect(chooserButton, "file-set", G_CALLBACK(load_image), data);
    g_signal_connect(apply_rotate, "clicked", G_CALLBACK(rotate_update), data);
    g_signal_connect(apply_filter, "clicked", G_CALLBACK(filter_update), data);
    g_signal_connect(auto_filter, "clicked", G_CALLBACK(filter_auto), data);
    g_signal_connect(auto_rotate, "clicked", G_CALLBACK(rotate_auto), data);

    menu_signals(builder);

    // Run the main window.
    gtk_main();
    free(data);
    

    return builder;
}
