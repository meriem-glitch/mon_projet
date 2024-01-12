#include <gtk/gtk.h>

// ... (rest of the code)

// Function to animate the list
void animate_list(LinkedList *list) {
    // Set the initial position of the nodes
    double node_x = 50.0;
    double node_y = 50.0;
    double rectangle_width = 80.0;
    double rectangle_height = 40.0;
    double horizontal_spacing = 20.0;
    Node *current = list->head;

    // Draw each node in the list
    while (current != NULL) {
        double x = node_x;
        double y = node_y;
        double node_x = x + rectangle_width + horizontal_spacing;

        // Draw the nodes
        // ... (drawing code)

        // Update the position of the nodes
        current = current->next;
    }

    // Update the position of the nodes
    // ... (update code)

    // Redraw the widget
    gtk_widget_queue_draw(drawing_area);
}

// Function to handle user interactions
void on_draw_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    LinkedList *list = (LinkedList *)user_data;

    // Set the initial position of the nodes
    double node_x = 50.0;
    double node_y = 50.0;
    double rectangle_width = 80.0;
    double rectangle_height = 40.0;
    double horizontal_spacing = 20.0;
    Node *current = list->head;

    // Draw each node in the list
    while (current != NULL) {
        double x = node_x;
        double y = node_y;
        double node_x = x + rectangle_width + horizontal_spacing;

        // Draw the nodes
        // ... (drawing code)

        // Update the position of the nodes
        current = current->next;
    }

    // Update the position of the nodes
    // ... (update code)

    // Redraw the widget
    gtk_widget_queue_draw(drawing_area);
}

// ... (rest of the code)

int main(int argc, char *argv[]) {
    // ... (main code)

    // Create a new GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Doubly Linked List GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 150);

    // Create a new drawing area
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 800, 100);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), &my_list);

    // ... (rest of the main code)

    // Set the initial position of the nodes
    double node_x = 50.0;
    double node_y = 50.0;
    double rectangle_width = 80.0;
    double rectangle_height = 40.0;
    double horizontal_spacing = 20.0;
    Node *current = list->head;

    // Draw each node in the list
    while (current != NULL) {
        double x = node_x;
        double y = node_y;
        double node_x = x + rectangle_width + horizontal_spacing;

        // Draw the nodes
        // ... (drawing code)

        // Update the position of the nodes
        current = current->next;
    }

    // Update the position of the nodes
    // ... (update code)

    // Redraw the widget
    gtk_widget_queue_draw(drawing_area);

    // ... (rest of the main code)

    // Set the initial position of the nodes
    double node_x = 50.0;
    double node_y = 50.0;
    double rectangle_width = 80.0;
    double rectangle_height = 40.0;
    double horizontal_spacing = 20.0;
    Node *current = list->head;

    // Draw each node in the list
    while (current != NULL) {
        double x = node_x;
        double y = node_y;
        double node_x = x + rectangle_width + horizontal_spacing;

        // Draw the nodes
        // ... (drawing code)

        // Update the position of the nodes
        current = current->next;
    }

    // Update the position of the nodes
    // ... (update code)

    // Redraw the widget
    gtk_widget_queue_draw(drawing_area);

    // ... (rest of the main code)

    return 0;
}