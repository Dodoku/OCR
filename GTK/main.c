#include <gtk/gtk.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>


GtkBuilder* builder;

//Global variable for Widget
GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *filename;
GtkWidget *confirmbutton;
GtkWidget *nbblur;

GtkWidget *frame1;
GtkWidget *frame2;
GtkWidget *frame3;
GtkWidget *frame4;
GtkWidget *frame5;

GtkWidget *image1;
GtkWidget *image2;
GtkWidget *displayimage;
GtkWidget *fixedf5;

GtkWidget *timer;

void on_filename_file_set(GtkFileChooserButton* f)
{
    //printf("file name = %s\n", gtk_chooser_get_filename(GTK_FILE_CHOOSER(f)));
    //printf("folder name = %s\n",gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(f)));
}
void on_confirmbutton_activate(GtkButton *b)
{
    //printf("file name = %s\n", gtk_chooser_get_filename(GTK_FILE_CHOOSER(filename)));
    //printf("folder name = %s\n",gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(filename)));
}

void on_nbblur_change_value(GtkButton* b)
{
    char tmp [128];
    gdouble val = gtk_spin_button_get_value(GTK_SPIN_BUTTON(nbblur));

    //sprintf(tmp,"spin = %d",(int) val);
    //gtk_label_set_text(GTK_LABEL(label),(const gchar*) tmp);
}

void on_displayimage_clicked(GtkButton* b)
{
    char filename[] = "sudoku.png";

    char cmd[2048];

    FILE *f1;

    int j,h,v,hor = 200, ver = 75;

    if(image1)
    {
        gtk_container_remove(GTK_CONTAINER(fixedf5),image1); //dire où et qui remove
    }
    gtk_widget_hide(image2);

    sprintf(cmd,"identify -format %%wx%%h \"%s\"\n", filename);

    f1 =popen(cmd,"r");

    strcpy(cmd,"");

    fgets(cmd,512,f1);
    fclose(f1);

    h = v = 1;

    if(strlen(cmd))
    {
        for(j = 0;j<strlen(cmd)-1;j++)if(cmd[j] == 'x')break;

        if(cmd[j] == 'x')
        {
            cmd[j] = 0;
            sscanf(cmd,"%d",&h);
            sscanf(&cmd[j+1],"%d", &v);
        }
    }

    if(h<100 ||v<100)
    {
        printf("**** questionable image: %s\n",filename);
        return;
    }

    int width = 420;
    int height = 250;
    
    sprintf(cmd, "convert \"%s \" -resize %dx%d tmp.jpg", filename,width,height);

    system(cmd);

    strcpy(filename,"tmp.jpg");

    sprintf(cmd,"identify -format %%wx%%h \"%s\"\n", filename);

    f1 =popen(cmd,"r");

    strcpy(cmd,"");

    fgets(cmd,512,f1);
    fclose(f1);

    h = v = 1;

    if(strlen(cmd))
    {
        for(j = 0;j<strlen(cmd)-1;j++)if(cmd[j] == 'x')break;
        
        if(cmd[j] == 'x')
        {
            cmd[j] = 0;   
            sscanf(cmd,"%d",&h);
            sscanf(&cmd[j+1],"%d", &v);
        }
        
    }

    image1 = gtk_image_new_from_file(filename);

    gtk_container_add(GTK_CONTAINER(fixedf5),image1);

    gtk_widget_show(image1);

    gtk_fixed_move(GTK_FIXED(fixedf5),image1,hor,ver);

    system("rm tmp.jpg");
}

gboolean timer_handler(GtkWidget *timer)
{
    time_t t = time(0);
    gtk_label_set_text(GTK_LABEL(timer),ctime(&t));
    return TRUE;
}

int main(int argc, char *argv[])
{
    gtk_init(&argc,&argv); //needed to use Gtk
    builder = gtk_builder_new_from_file("gtk.glade"); //build glade file with name file

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); //limit the resize of window


    //get the widget
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));
    filename = GTK_WIDGET(gtk_builder_get_object(builder,"filename"));
    confirmbutton = GTK_WIDGET(gtk_builder_get_object(builder,"confirmbutton"));
    nbblur = GTK_WIDGET(gtk_builder_get_object(builder,"nbblur"));

    frame1 = GTK_WIDGET(gtk_builder_get_object(builder,"frame1"));
    frame2 = GTK_WIDGET(gtk_builder_get_object(builder,"frame2"));
    frame3 = GTK_WIDGET(gtk_builder_get_object(builder,"frame3"));
    frame4 = GTK_WIDGET(gtk_builder_get_object(builder,"frame4"));
    frame5 = GTK_WIDGET(gtk_builder_get_object(builder,"frame5"));

    displayimage = GTK_WIDGET(gtk_builder_get_object(builder,"displayimage"));
    image2 = GTK_WIDGET(gtk_builder_get_object(builder,"image2"));
    image1 = NULL;
    fixedf5 = GTK_WIDGET(gtk_builder_get_object(builder,"fixedf5"));

    timer = GTK_WIDGET(gtk_builder_get_object(builder,"timer"));


    //set the color of the window
    //GdkRGBA color;

    GdkColor color;
    color.red = 0x3333;
    color.green = 0x3333;
    color.blue = 0x3333;
    //gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_NORMAL,&color);

    gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL,&color);

    //set frame color
    
    gtk_widget_modify_bg(frame1, GTK_STATE_NORMAL,&color);

    
    gtk_widget_modify_bg(frame2, GTK_STATE_NORMAL,&color);

    
    gtk_widget_modify_bg(frame3, GTK_STATE_NORMAL,&color);

    
    gtk_widget_modify_bg(frame4, GTK_STATE_NORMAL,&color);

    
    gtk_widget_modify_bg(frame5, GTK_STATE_NORMAL,&color);

    //timer
    guint ID = g_timeout_add_seconds(1,(GSourceFunc)timer_handler,timer);

    //signal
    g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_builder_connect_signals(builder,NULL);
    

    //Show and run the window
    gtk_widget_show(window);
    gtk_main();
    return EXIT_SUCCESS;
}