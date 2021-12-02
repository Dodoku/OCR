#include <stdlib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <math.h>

#include "gui.h"
#include "../tools/image.h"
#include "train_gui.h"

#include "../imageProcess/rotate.h"

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
// Thread to update the gui
//------------------------------------------------------------------------------

static void* refresh_image_rotate(void * p_data){
    int angle = *((int*)p_data);
    free((int*)p_data);
    GtkImage* rotateImage = GTK_IMAGE(gtk_builder_get_object(data->builder, 
                                                            "rotate_image"));
    data->editedImage = copy(data->loadImage);
    if(angle >= -180 && angle <= 180)
        data->editedImage = rotate(data->editedImage, angle*M_PI/180);
    GdkPixbuf *pixbuf = gtk_image_new_from_sdl_surface(data->editedImage);

    int width = gdk_pixbuf_get_width (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    width = (double)width * ((double)300/height);
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, 300, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(rotateImage, pixbuf);
    return NULL;
}
//------------------------------------------------------------------------------
// EVENTS
//------------------------------------------------------------------------------

void rotate_update(){
    GtkRange *scale = GTK_RANGE(gtk_builder_get_object(data->builder, "rotation_slider"));
    int *angle = malloc(sizeof(int));
    *angle = gtk_range_get_value(scale);
    
    pthread_cancel(data->thread);
    pthread_create(&data->thread, NULL, refresh_image_rotate, angle);
}

void load_image(GtkFileChooserButton *button, gpointer user_data){
    struct gui_data *Data = user_data;

    if(Data->loadImage != NULL)
        SDL_FreeSurface(Data->loadImage);
    
    if(Data->editedImage != NULL)
        SDL_FreeSurface(Data->editedImage);

    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
    Data->loadImage = load(filename);
    int *angle = malloc(sizeof(int));
    *angle = -999;
    pthread_create(&data->thread, NULL, refresh_image_rotate, angle);

    GtkWidget* confirmButton = GTK_WIDGET(gtk_builder_get_object(Data->builder, 
                                                            "confirmbutton"));
    GtkWidget* stack = GTK_WIDGET(gtk_builder_get_object(Data->builder, 
                                                            "stack1"));

    gtk_widget_set_sensitive(confirmButton, TRUE);
    gtk_widget_set_sensitive(stack, TRUE);
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

    // Gets the widgets.
    GtkWindow* mainWindow = GTK_WINDOW(gtk_builder_get_object(builder, 
                                                            "org.dodoku.main"));
    GtkFileChooserButton* chooserButton = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, 
                                                            "filename"));
    GtkButton* apply_rotate = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                            "apply_rotate"));

    if (gtk_window_set_icon_from_file(mainWindow, "res/logo.png", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return NULL;
    }

    // Connects event handlers.
    g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Buttons event handlers.
    g_signal_connect(GTK_MENU_ITEM(gtk_builder_get_object(builder, "train_tools")), 
                                    "activate", G_CALLBACK(open_train_gui), builder);
    g_signal_connect(chooserButton, "file-set", G_CALLBACK(load_image), data);
    g_signal_connect(apply_rotate, "clicked", G_CALLBACK(rotate_update), data);


    // Run the main window.
    gtk_main();
    free(data);
    

    return builder;
}