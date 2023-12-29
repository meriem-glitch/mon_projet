#include <gtk/gtk.h>
#include <math.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} LinkedList;

// Function prototypes
void add_element(LinkedList *list, int value);
gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void draw_arrow(cairo_t *cr, double x1, double y1, double x2, double y2);
void insert_element(LinkedList *list, int value);
void delete_element(LinkedList *list, int value);
void on_button_clicked(GtkWidget *widget, gpointer user_data);
void on_insert_button_clicked(GtkWidget *widget, gpointer user_data);
void on_insert_after_display_button_clicked(GtkWidget *widget, gpointer user_data);
void on_delete_button_clicked(GtkWidget *widget, gpointer user_data);
void on_search_button_clicked(GtkWidget *widget, gpointer user_data);
void search_value_in_list(LinkedList *list, int value);
// Déclarations supplémentaires
gboolean on_draw_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
gboolean on_draw_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer user_data);
gboolean on_draw_button_release(GtkWidget *widget, GdkEventButton *event, gpointer user_data);

// Ajoutez une variable globale pour stocker l'état du déplacement
gboolean is_dragging = FALSE;
Node *selected_node = NULL;

// Global linked list
LinkedList my_list = {NULL, NULL};

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Doubly Linked List GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 150);

    GtkWidget *label_elements = gtk_label_new("Enter elements separated by space:");
    GtkWidget *entry_elements = gtk_entry_new();

    GtkWidget *button_show = gtk_button_new_with_label("Show Doubly Linked List");
    GtkWidget *button_insert = gtk_button_new_with_label("Insert Element");
    GtkWidget *button_insert_after_display = gtk_button_new_with_label("Insert After Display");
    GtkWidget *button_delete = gtk_button_new_with_label("Delete");
    GtkWidget *button_search = gtk_button_new_with_label("Search Value");

    g_signal_connect(button_show, "clicked", G_CALLBACK(on_button_clicked), entry_elements);
    g_signal_connect(button_insert, "clicked", G_CALLBACK(on_insert_button_clicked), window);
    g_signal_connect(button_insert_after_display, "clicked", G_CALLBACK(on_insert_after_display_button_clicked), window);
    g_signal_connect(button_delete, "clicked", G_CALLBACK(on_delete_button_clicked), window);
    g_signal_connect(button_search, "clicked", G_CALLBACK(on_search_button_clicked), window);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(box), label_elements);
    gtk_container_add(GTK_CONTAINER(box), entry_elements);
    gtk_container_add(GTK_CONTAINER(box), button_show);
    gtk_container_add(GTK_CONTAINER(box), button_insert);
    gtk_container_add(GTK_CONTAINER(box), button_insert_after_display);
    gtk_container_add(GTK_CONTAINER(box), button_delete);
    gtk_container_add(GTK_CONTAINER(box), button_search);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);

    gtk_main();

    // Free allocated memory before exiting
    Node *current = my_list.head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        g_free(temp);
    }

    return 0;
}

void add_element(LinkedList *list, int value) {
    Node *new_node = g_new(Node, 1);
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (list->head == NULL) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    LinkedList *list = (LinkedList *)user_data;

    double x = 50.0, y = 50.0;
    double rectangle_width = 80.0;
    double rectangle_height = 40.0;
    double horizontal_spacing = 20.0;

    Node *current = list->head;
    while (current != NULL) {
        cairo_rectangle(cr, x, y, rectangle_width, rectangle_height);
        cairo_stroke_preserve(cr);
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        cairo_fill(cr);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_font_size(cr, 16.0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_move_to(cr, x + 10, y + 30);
        char text[10];
        sprintf(text, "%d", current->value);
        cairo_show_text(cr, text);

        if (current->next != NULL) {
            double next_x = x + rectangle_width + horizontal_spacing;
            double next_y = y + rectangle_height / 2;
            draw_arrow(cr, x + rectangle_width, y + rectangle_height / 2, next_x, next_y);
        }

        x += rectangle_width + horizontal_spacing;

        current = current->next;
    }

    return FALSE;
}

void draw_arrow(cairo_t *cr, double x1, double y1, double x2, double y2) {
    cairo_save(cr);

    double angle = atan2(y2 - y1, x2 - x1);
    double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    cairo_translate(cr, x1, y1);
    cairo_rotate(cr, angle);
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, length, 0);
    cairo_line_to(cr, length - 10, -5);
    cairo_line_to(cr, length - 10, 5);
    cairo_close_path(cr);

    cairo_fill(cr);

    cairo_restore(cr);
}

void insert_element(LinkedList *list, int value) {
    Node *new_node = g_new(Node, 1);
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (list->head == NULL) {
        list->head = list->tail = new_node;
        return;
    }

    Node *current = list->head;

    while (current != NULL && current->value <= value) {
        current = current->next;
    }

    if (current != NULL) {
        new_node->prev = current->prev;
        new_node->next = current;

        if (current->prev != NULL) {
            current->prev->next = new_node;
        } else {
            list->head = new_node;
        }

        current->prev = new_node;
    } else {
        // If the value is greater than all existing values, add it to the end
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void delete_element(LinkedList *list, int value) {
    if (list->head == NULL) {
        return; // Liste vide, ne rien faire
    }

    Node *current = list->head;

    while (current != NULL && current->value != value) {
        current = current->next;
    }

    if (current != NULL) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            list->head = current->next;
        }

        if (current->next != NULL) {
            current->next->prev = current->prev;
        } else {
            list->tail = current->prev;
        }

        g_free(current);
    }
}

void search_value_in_list(LinkedList *list, int value) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            g_print("Value %d found in the list.\n", value);
            return;
        }
        current = current->next;
    }

    g_print("Value %d not found in the list.\n", value);
}

void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *entry_elements = GTK_ENTRY(user_data);
    const gchar *elements_text = gtk_entry_get_text(entry_elements);

    gchar **elements = g_strsplit(elements_text, " ", -1);
    for (int i = 0; elements[i] != NULL; ++i) {
        int value = atoi(elements[i]);
        insert_element(&my_list, value);
    }

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Doubly Linked List GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 150);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 800, 100);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), &my_list);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(box), drawing_area);

    GtkWidget *button_insert_after_display = gtk_button_new_with_label("Insert After Display");
    g_signal_connect(button_insert_after_display, "clicked", G_CALLBACK(on_insert_after_display_button_clicked), window);
    gtk_container_add(GTK_CONTAINER(box), button_insert_after_display);

    GtkWidget *button_delete = gtk_button_new_with_label("Delete");
    g_signal_connect(button_delete, "clicked", G_CALLBACK(on_delete_button_clicked), window);
    gtk_container_add(GTK_CONTAINER(box), button_delete);

    GtkWidget *button_search = gtk_button_new_with_label("Search Value");
    g_signal_connect(button_search, "clicked", G_CALLBACK(on_search_button_clicked), window);
    gtk_container_add(GTK_CONTAINER(box), button_search);

    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
}

void on_insert_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *entry_value;
    gint result;

    dialog = gtk_dialog_new_with_buttons("Insert Element",
                                         GTK_WINDOW(user_data),
                                         GTK_DIALOG_MODAL,
                                         "Insert",
                                         GTK_RESPONSE_ACCEPT,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    entry_value = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_value), "Value to insert");
    gtk_container_add(GTK_CONTAINER(content_area), entry_value);

    gtk_widget_show_all(dialog);

    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        const gchar *value_text = gtk_entry_get_text(GTK_ENTRY(entry_value));
        int value = atoi(value_text);
        insert_element(&my_list, value);
        gtk_widget_queue_draw(GTK_WIDGET(user_data));
    }

    gtk_widget_destroy(dialog);
}

void on_insert_after_display_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *entry_value;
    gint result;

    dialog = gtk_dialog_new_with_buttons("Insert After Display",
                                         GTK_WINDOW(user_data),
                                         GTK_DIALOG_MODAL,
                                         "Insert",
                                         GTK_RESPONSE_ACCEPT,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    entry_value = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_value), "Value to insert");
    gtk_container_add(GTK_CONTAINER(content_area), entry_value);

    gtk_widget_show_all(dialog);

    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        const gchar *value_text = gtk_entry_get_text(GTK_ENTRY(entry_value));
        int value = atoi(value_text);
        insert_element(&my_list, value);
        gtk_widget_queue_draw(GTK_WIDGET(user_data));
    }

    gtk_widget_destroy(dialog);
}

void on_delete_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *entry_value;
    gint result;

    dialog = gtk_dialog_new_with_buttons("Delete Element",
                                         GTK_WINDOW(user_data),
                                         GTK_DIALOG_MODAL,
                                         "Delete",
                                         GTK_RESPONSE_ACCEPT,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    entry_value = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_value), "Value to delete");
    gtk_container_add(GTK_CONTAINER(content_area), entry_value);

    gtk_widget_show_all(dialog);

    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        const gchar *value_text = gtk_entry_get_text(GTK_ENTRY(entry_value));
        int value = atoi(value_text);
        delete_element(&my_list, value);
        gtk_widget_queue_draw(GTK_WIDGET(user_data));
    }

    gtk_widget_destroy(dialog);
}

void on_search_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *entry_value;
    gint result;

    dialog = gtk_dialog_new_with_buttons("Search Value",
                                         GTK_WINDOW(user_data),
                                         GTK_DIALOG_MODAL,
                                         "Search",
                                         GTK_RESPONSE_ACCEPT,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    entry_value = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_value), "Value to search");
    gtk_container_add(GTK_CONTAINER(content_area), entry_value);

    gtk_widget_show_all(dialog);

    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT) {
        const gchar *value_text = gtk_entry_get_text(GTK_ENTRY(entry_value));
        int value = atoi(value_text);
        search_value_in_list(&my_list, value);
    }

    gtk_widget_destroy(dialog);
}