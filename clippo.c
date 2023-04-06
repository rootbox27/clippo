#include <gtk/gtk.h>

// Define the maximum number of items to store in the clipboard history
#define MAX_ITEMS 50

// Global variables for the clipboard history and current index
char* clipboard_history[MAX_ITEMS];
int current_index = 0;

// Callback function for the "Paste" button
void paste_callback(GtkWidget *widget, gpointer data)
{
    // Get the currently selected item in the clipboard history
    char* selected_item = clipboard_history[current_index];
    
    // Copy the selected item to the system clipboard
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    gtk_clipboard_set_text(clipboard, selected_item, -1);
}

// Callback function for the "Next" button
void next_callback(GtkWidget *widget, gpointer data)
{
    // Move to the next item in the clipboard history
    if (current_index < MAX_ITEMS - 1) {
        current_index++;
    } else {
        current_index = 0;
    }
    
    // Update the label to display the selected item
    gtk_label_set_text(GTK_LABEL(data), clipboard_history[current_index]);
}

// Callback function for the "Previous" button
void prev_callback(GtkWidget *widget, gpointer data)
{
    // Move to the previous item in the clipboard history
    if (current_index > 0) {
        current_index--;
    } else {
        current_index = MAX_ITEMS - 1;
    }
    
    // Update the label to display the selected item
    gtk_label_set_text(GTK_LABEL(data), clipboard_history[current_index]);
}

int main(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);
    
    // Create a window and set its title
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Smart Clipboard");
    
    // Create a vertical box to hold the widgets
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Create a label to display the currently selected item in the clipboard history
    GtkWidget *label = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    
    // Create a horizontal box to hold the navigation buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    
    // Create the "Previous" button and connect it to its callback function
    GtkWidget *prev_button = gtk_button_new_with_label("Previous");
    g_signal_connect(prev_button, "clicked", G_CALLBACK(prev_callback), label);
    gtk_box_pack_start(GTK_BOX(hbox), prev_button, FALSE, FALSE, 0);
    
    // Create the "Paste" button and connect it to its callback function
    GtkWidget *paste_button = gtk_button_new_with_label("Paste");
    g_signal_connect(paste_button, "clicked", G_CALLBACK(paste_callback), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), paste_button, FALSE, FALSE, 0);
    
    // Create the "Next" button and connect it to its callback function
    GtkWidget *next_button = gtk_button_new_with_label("Next");
    g_signal_connect(next_button, "clicked", G_CALLBACK(next_callback), label);
    gtk_box_pack_start(GTK_BOX(hbox), next_button, FALSE, FALSE, 0);
    
    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

