#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <pthread.h>

#include "gui.h"
#include "../neuralNetwork/neuralNetwork.h"
#include "../neuralNetwork/dataLoader.h"
#include "../neuralNetwork/number.h"


void open_train_button(GtkFileChooserButton *button, gpointer user_data){
    GtkBuilder *builder = user_data;

    char *path = (char*) gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));

    GtkLabel* images = GTK_LABEL(gtk_builder_get_object(builder, 
                                                           "open_text"));

    GtkWidget* spin = GTK_WIDGET(gtk_builder_get_object(builder, 
                                                           "trainings_spin"));
    GtkWidget* start_train = GTK_WIDGET(gtk_builder_get_object(builder, 
                                                           "start_train_button"));

    FILE *fp = fopen(path, "r");
    
    if(!fp){
        error_message("Error opening file");
        gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(button));
        return;
    }

    int lines = countLines(fp);
    char buildText[80];
    sprintf(buildText, "%i images loaded", lines - 1);
 	gtk_label_set_text(images, buildText);
    
    gtk_widget_set_sensitive(spin, TRUE);
    gtk_widget_set_sensitive(start_train, TRUE);
}

struct start_network_args {
    char *path;
    int loop;
    GtkLabel* error_rate;
    GtkLabel* trainings_loop;
};

static void *start_network(void * p_data){

    struct start_network_args *args = p_data;
    Network network = init_number();
    train_number_with_gui(&network, args->path, args->loop, 
                                    args->error_rate, args->trainings_loop);
    free(args);
}

gboolean lunch_training(gpointer user_data){

        GtkBuilder *builder = user_data;

        GtkFileChooserButton* openTrain = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, 
                                                        "open_train_button"));

        GtkSpinButton* spin = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, 
                                                           "trainings_spin"));

        GtkLabel* error_rate = GTK_LABEL(gtk_builder_get_object(builder, 
                                                            "error_rate_value_label"));
        GtkLabel* trainings_loop = GTK_LABEL(gtk_builder_get_object(builder, 
                                                            "trainings_loop_value_label"));

        char *loadPath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(openTrain));

        int loop = (int) gtk_spin_button_get_value(spin);
        char trains_loop_str[50];
        sprintf(trains_loop_str, "%i / %i", 0, loop);
        gtk_label_set_text(trainings_loop, trains_loop_str);

        struct start_network_args *args = malloc(sizeof(struct start_network_args));
        args->path = loadPath;
        args->loop = loop;
        args->error_rate = error_rate;
        args->trainings_loop = trainings_loop;
        
        pthread_t thread;
        pthread_create(&thread, NULL, start_network, args);

        printf("FInished\n");
        return FALSE;
}

void start_train_button(GtkButton *start_train, gpointer user_data){
    GtkBuilder *builder = user_data;

    GtkWindow* trainWindow = GTK_WINDOW(gtk_builder_get_object(builder, 
                                                           "org.dodoku.train"));
    GtkFileChooserButton* openTrain = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, 
                                                        "open_train_button"));
    GtkSpinButton* spin = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, 
                                                           "trainings_spin"));

    char *filename;
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Save Output File",
                                        trainWindow,
                                        action,
                                        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                        GTK_STOCK_SAVE,GTK_RESPONSE_ACCEPT,
                                        NULL);
    chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);

    gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_window_close(GTK_WINDOW(dialog));
    gtk_widget_destroy(dialog);
    if (res == GTK_RESPONSE_ACCEPT)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(openTrain), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(spin), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(start_train), FALSE);
        g_timeout_add_full(G_PRIORITY_DEFAULT, 100, lunch_training, builder, NULL);
    }
}

void open_train_gui(GtkButton *button, gpointer user_data){
    GtkBuilder *builder =  user_data;

    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "res/dodoku_train.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return NULL;
    }

    GtkWindow* trainWindow = GTK_WINDOW(gtk_builder_get_object(builder, 
                                                           "org.dodoku.train"));
    GtkFileChooserButton* openTrain = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, 
                                                           "open_train_button"));
    GtkButton* start_train = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                           "start_train_button"));

    // Buttons event handlers.
    g_signal_connect(openTrain, "file-set", G_CALLBACK(open_train_button), builder);
    g_signal_connect(start_train, "clicked", G_CALLBACK(start_train_button), builder);

    gtk_widget_show_now(GTK_WIDGET(trainWindow));
}