#include <stdlib.h>
#include <gtk/gtk.h>

#include "train_gui.h"

void error_message(char *message)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
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
    

    // Gets the widgets.
    GtkWindow* mainWindow = GTK_WINDOW(gtk_builder_get_object(builder, 
                                                            "org.dodoku.main"));
    GtkButton* trainButton = GTK_BUTTON(gtk_builder_get_object(builder, 
                                                            "train_button"));

    // Connects event handlers.
    g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    // Buttons event handlers.
    g_signal_connect(trainButton, "clicked", G_CALLBACK(open_train_gui), builder);


    // Run the main window.
    gtk_main();

    

    return builder;
}