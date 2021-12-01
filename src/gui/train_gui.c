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
    char *pathToSave;
    int loop;
    GtkBuilder *builder;
    GtkLabel* error_rate;
    GtkLabel* trainings_loop;
};

static void *lunch_training(void * p_data){

        struct start_network_args *args = p_data;

        char trains_loop_str[50];
        sprintf(trains_loop_str, "%i / %i", 0, args->loop);
        gtk_label_set_text(args->trainings_loop, trains_loop_str);

        Network network = init_number();
        train_number_with_gui(&network, args->path, args->loop, 
                                    args->error_rate, args->trainings_loop);
        
        save_network(&network, args->pathToSave);
        free_network(&network);

        info_message("Training completed");

        GtkButton* start_train = GTK_BUTTON(gtk_builder_get_object(args->builder, 
                                                           "start_train_button"));
        GtkFileChooserButton* openTrain = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(args->builder, 
                                                        "open_train_button"));
        GtkSpinButton* spin = GTK_SPIN_BUTTON(gtk_builder_get_object(args->builder, 
                                                           "trainings_spin"));
        gtk_widget_set_sensitive(GTK_WIDGET(openTrain), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(spin), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(start_train), TRUE);
        free(args);
        return NULL;
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
                                        g_dgettext("gtk30", "Cancel"),GTK_RESPONSE_CANCEL,
                                        g_dgettext("gtk30", "Save"),GTK_RESPONSE_ACCEPT,
                                        NULL);
    
    chooser = GTK_FILE_CHOOSER (dialog);
    gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "record.data");

    char *loadPath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(openTrain));

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    
    filename = gtk_file_chooser_get_filename (chooser);
    gtk_window_close(GTK_WINDOW(dialog));
    gtk_widget_destroy(dialog);
    if (res == GTK_RESPONSE_ACCEPT)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(openTrain), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(spin), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(start_train), FALSE);
        struct start_network_args *args = malloc(sizeof(struct start_network_args));
        args->path = loadPath;
        args->pathToSave = filename;
        args->loop = (int) gtk_spin_button_get_value(spin);
        args->builder = builder;
        args->error_rate = GTK_LABEL(gtk_builder_get_object(builder, 
                                                            "error_rate_value_label"));
        args->trainings_loop = GTK_LABEL(gtk_builder_get_object(builder,
                                                            "trainings_loop_value_label"));
        pthread_t thread;
        pthread_create(&thread, NULL, lunch_training, args);
    }
}

void open_train_gui(GtkButton *button, gpointer user_data){
    GtkBuilder *builder =  user_data;
    GError* error = NULL;
    gtk_button_get_event_window (button);

    if (gtk_builder_add_from_file(builder, "res/dodoku_train.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
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