#include "page_garde.h"
#include "page_presentation.h"
#include <gtk/gtk.h>
void afficher_page_presentation(GtkWidget *parent) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *titre_label;
    GtkWidget *paragraphe_textview;
    GtkWidget *sous_titre_label;
    GtkWidget *autre_paragraphe_textview;
    GtkWidget *deuxieme_titre_label;
    GtkWidget *deuxieme_paragraphe_textview;

    // Création de la boîte de dialogue
    dialog = gtk_dialog_new_with_buttons("Présentation",
                                         GTK_WINDOW(parent),
                                         GTK_DIALOG_MODAL,
                                         "Commencer",
                                         GTK_RESPONSE_OK,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Ajout du titre à la zone de contenu
    titre_label = creer_titre("Bienvenue dans notre programme de tri de liste doublement chaînée !");
    gtk_container_add(GTK_CONTAINER(content_area), titre_label);

    // Ajout du premier paragraphe
    paragraphe_textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(paragraphe_textview), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(paragraphe_textview), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(paragraphe_textview), FALSE);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(paragraphe_textview), 12);

    GtkTextBuffer *buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(paragraphe_textview));
    const gchar *paragraphe_text = "Une liste doublement chaînée est une structure de données linéaire. Chaque élément contient une valeur et deux pointeurs qui indiquent l'élément suivant et l'élément précédent. Cette structure de données permet des insertions et suppressions rapides dans la liste.";
    gtk_text_buffer_set_text(buffer1, paragraphe_text, -1);

    gtk_container_add(GTK_CONTAINER(content_area), paragraphe_textview);

    // Ajout d'une séparation
    GtkWidget *separator1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(content_area), separator1);

    // Ajout du sous-titre à la zone de contenu
    sous_titre_label = creer_titre("Fonctionnement de la méthode de tri à bulle");
    gtk_container_add(GTK_CONTAINER(content_area), sous_titre_label);

    // Ajout du deuxième paragraphe
    autre_paragraphe_textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(autre_paragraphe_textview), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(autre_paragraphe_textview), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(autre_paragraphe_textview), FALSE);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(autre_paragraphe_textview), 12);

    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(autre_paragraphe_textview));
    const gchar *autre_paragraphe_text = "La méthode de tri à bulle est un algorithme de tri simple qui parcourt la liste plusieurs fois. Lors de chaque parcours, les éléments sont comparés et échangés si nécessaire. Le tri se termine lorsque aucun échange n'est effectué.";
    gtk_text_buffer_set_text(buffer2, autre_paragraphe_text, -1);

    gtk_container_add(GTK_CONTAINER(content_area), autre_paragraphe_textview);

    // Ajout d'une séparation
    GtkWidget *separator2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(content_area), separator2);

    // Ajout d'un deuxième titre
    deuxieme_titre_label = creer_titre("Avantages et limites de la méthode");
    gtk_container_add(GTK_CONTAINER(content_area), deuxieme_titre_label);

    // Ajout d'un deuxième paragraphe
    deuxieme_paragraphe_textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(deuxieme_paragraphe_textview), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(deuxieme_paragraphe_textview), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(deuxieme_paragraphe_textview), FALSE);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(deuxieme_paragraphe_textview), 12);

    GtkTextBuffer *buffer3 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(deuxieme_paragraphe_textview));
    const gchar *deuxieme_paragraphe_text = "La méthode de tri à bulle a l'avantage d'être simple à implémenter et de trier des petites listes de manière efficace. Cependant, elle est moins efficace pour des listes de grande taille et son temps d'exécution est plus long que les autres algorithmes.";
    gtk_text_buffer_set_text(buffer3, deuxieme_paragraphe_text, -1);

    gtk_container_add(GTK_CONTAINER(content_area), deuxieme_paragraphe_textview);

    // Affichage de la boîte de dialogue
    gtk_widget_show_all(dialog);

    // Exécution de la boîte de dialogue
    gtk_dialog_run(GTK_DIALOG(dialog));

    // Fermeture de la boîte de dialogue après utilisation
    gtk_widget_destroy(dialog);
}