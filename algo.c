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

// Fonction de tri à bulles
void bubble_sort(LinkedList *list) {
    if (list->head == NULL || list->head->next == NULL) {
        // La liste est déjà triée ou vide
        return;
    }

    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) {
            if (ptr1->value > ptr1->next->value) {
                // Échange des éléments
                int temp = ptr1->value;
                ptr1->value = ptr1->next->value;
                ptr1->next->value = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Fonction de dessin
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

// Fonction d'affichage de la flèche
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

// Fonction d'insertion d'élément dans la liste
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
        // Si la valeur est plus grande que toutes les valeurs existantes, ajoutez-la à la fin
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

// Fonction de suppression d'élément de la liste
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

// Fonction de recherche de valeur dans la liste
void search_value_in_list(LinkedList *list, int value) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            g_print("La valeur %d a été trouvée dans la liste.\n", value);
            return;
        }
        current = current->next;
    }

    g_print("La valeur %d n'a pas été trouvée dans la liste.\n", value);
}

// Fonction de gestion du clic sur le bouton
void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *entry_elements = GTK_ENTRY(user_data);
    const gchar *elements_text = gtk_entry_get_text(entry_elements);

    gchar **elements = g_strsplit(elements_text, " ", -1);
    for (int i = 0; elements[i] != NULL; ++i) {
        int value = atoi(elements[i]);
        insert_element(&my_list, value);
    }

    // Appeler la fonction de tri à bulles après l'insertion des éléments
    bubble_sort(&my_list);

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

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Doubly Linked List GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 150);

    GtkWidget *label_elements = gtk_label_new("Entrez les éléments séparés par un espace :");
    GtkWidget *entry_elements = gtk_entry_new();

    GtkWidget *button_show = gtk_button_new_with_label("Afficher la liste doublement chaînée");
    GtkWidget *button_insert = gtk_button_new_with_label("Insérer un élément");
    GtkWidget *button_insert_after_display = gtk_button_new_with_label("Insérer après l'affichage");
    GtkWidget *button_delete = gtk_button_new_with_label("Supprimer");
    GtkWidget *button_search = gtk_button_new_with_label("Rechercher une valeur");

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

    // Libérer la mémoire allouée avant de quitter
    Node *current = my_list.head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        g_free(temp);
    }

    return 0;
}
