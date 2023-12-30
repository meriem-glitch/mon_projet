#include "page_garde.h"
#include <gtk/gtk.h>
#include "page_presentation.h"
GtkWidget* creer_titre(const gchar *text) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(label), text);

    // Ajout des propriétés ou du style au label si nécessaire
    PangoAttrList *attrs = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attrs, attr);
    attr = pango_attr_size_new(20 * PANGO_SCALE); // Taille de police plus grande (20 points)
    pango_attr_list_insert(attrs, attr);

    gtk_label_set_attributes(GTK_LABEL(label), attrs);
    pango_attr_list_unref(attrs);

    return label;
}

void afficher_page_de_garde(GtkWidget *parent) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *titre_label;
    GtkWidget *sous_titre_textview;
    GtkWidget *image;

    // Création d'une boîte de dialogue
    dialog = gtk_dialog_new_with_buttons("Page de Garde",
                                         GTK_WINDOW(parent),
                                         GTK_DIALOG_MODAL,
                                         "Continuer",
                                         GTK_RESPONSE_OK,
                                         NULL);

    // Récupération de la zone de contenu de la boîte de dialogue
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Ajout du titre à la zone de contenu
    titre_label = creer_titre("La liste doublement chaînée avec la méthode de tri à bulle");
    gtk_container_add(GTK_CONTAINER(content_area), titre_label);

    // Ajout de l'image à la zone de contenu
    image = gtk_image_new_from_file("photo_2023-12-30_22-11-18.jpg");
    if (!image) {
        g_warning("Échec du chargement de l'image !");
    } else {
        gtk_container_add(GTK_CONTAINER(content_area), image);
    }

    // Ajout du sous-titre à la zone de contenu
    sous_titre_textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(sous_titre_textview), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(sous_titre_textview), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(sous_titre_textview), FALSE);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(sous_titre_textview), 6);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sous_titre_textview));
    const gchar *sous_titre_text = "La liste doublement chaînée est une structure de données pratique pour stocker des éléments qui ont un ordre défini. Apprenez comment trier efficacement une liste doublement chaînée avec la méthode de tri à bulle.";
    gtk_text_buffer_set_text(buffer, sous_titre_text, -1);

    gtk_container_add(GTK_CONTAINER(content_area), sous_titre_textview);

    // Affichage de la boîte de dialogue
    gtk_widget_show_all(dialog);

    // Exécution de la boîte de dialogue
    gtk_dialog_run(GTK_DIALOG(dialog));

    // Fermeture de la boîte de dialogue après utilisation
    gtk_widget_destroy(dialog);
}