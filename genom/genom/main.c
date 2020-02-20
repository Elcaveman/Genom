#include <gtk/gtk.h>
#include "Greedy/assemblage.h"
#include "Recherche/recherche.h"

GtkBuilder *builder;

GtkWidget *main_win;
GtkWidget *authent_win;
GtkWidget *assemblage_win;
GtkWidget *assem_greedy_win;
GtkWidget *assem_dbn_win;
GtkWidget *search_win;


GtkEntry  *ndc;
GtkEntry  *psw;

GtkEntry   *input_greed;
GtkEntry   *output_greed;

GtkEntry  *k;
GtkEntry  *input_DBN;
GtkEntry  *output_DBN;

GtkEntry   *adn_sea;
GtkEntry   *virus_sea;


void show_main_win(GtkButton *button, gpointer user_data)
{
    char *username = gtk_entry_get_text(ndc);
    char *password = gtk_entry_get_text(psw);

    if (strcmp(username, "oudaoud")==0 && strcmp(password, "taha123")==0){

        gtk_widget_hide(authent_win);
        gtk_widget_show(main_win);
    }
    return;

}

void show_ass_win(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(assemblage_win);
    return;

}

void show_greed_win(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(assem_greedy_win);
    return;

}
void show_search_win(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(search_win);
    return;

}
void RECHERCHE(GtkButton *button, gpointer user_data){
    char* adn_file = gtk_entry_get_text(GTK_ENTRY(adn_sea));

    char* virus_file = gtk_entry_get_text(GTK_ENTRY(virus_sea));
    recherche(adn_file,virus_file);
    return;
}

void ASSEMBLAGE_GREED(GtkButton *button, gpointer user_data){
    char* inpt_file = gtk_entry_get_text(GTK_ENTRY(input_greed));

    char* outpt_file = gtk_entry_get_text(GTK_ENTRY(output_greed));
    Assemblage_greed(inpt_file,outpt_file);
    return;
}
void show_dbn_win(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(assem_dbn_win);
    return;
}
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "./main_win.glade", NULL);
    gtk_builder_add_from_file(builder, "./authent_win.glade", NULL);
    gtk_builder_add_from_file(builder, "./assemblage_win.glade", NULL);
    gtk_builder_add_from_file(builder, "./assem_greedy_win.glade", NULL);
    gtk_builder_add_from_file(builder, "./assem_DBN_win.glade", NULL);
    gtk_builder_add_from_file(builder, "./search_win.glade", NULL);

    main_win = GTK_WIDGET(gtk_builder_get_object(builder, "main_win"));
    assemblage_win = GTK_WIDGET(gtk_builder_get_object(builder, "assemblage_win"));
    authent_win = GTK_WIDGET(gtk_builder_get_object(builder, "authent_win"));
    assem_greedy_win = GTK_WIDGET(gtk_builder_get_object(builder, "assem_greedy_win"));
    assem_dbn_win = GTK_WIDGET(gtk_builder_get_object(builder, "assem_dbn_win"));
    search_win =  GTK_WIDGET(gtk_builder_get_object(builder, "search_win"));

    gtk_window_set_title (GTK_WINDOW (main_win), "ADN assembler");
    gtk_window_set_title (GTK_WINDOW (assemblage_win), "ADN assembler");
    gtk_window_set_title (GTK_WINDOW (authent_win), "ADN assembler");
    gtk_window_set_title (GTK_WINDOW (assem_greedy_win), "ADN assembler");
    gtk_window_set_title (GTK_WINDOW (search_win), "ADN assembler");

    /* the x button connectors*/
    g_signal_connect(main_win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //g_signal_connect(assemblage_win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(authent_win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* buttons declatation*/
    GtkButton *button_ass = GTK_BUTTON(gtk_builder_get_object(builder, "assemblage"));
    GtkButton *button_sea = GTK_BUTTON(gtk_builder_get_object(builder, "recherche"));
    GtkButton *button_quit = GTK_BUTTON(gtk_builder_get_object(builder, "quiter"));

    GtkButton *button_dbn = GTK_BUTTON(gtk_builder_get_object(builder, "assemblage_dbn"));
    GtkButton *button_greed = GTK_BUTTON(gtk_builder_get_object(builder, "assemblage_greedy"));

    GtkButton *button_conn = GTK_BUTTON(gtk_builder_get_object(builder, "connection"));

    GtkButton *button_greed_asm = GTK_BUTTON(gtk_builder_get_object(builder, "greedy_asm"));
    GtkButton *button_dbn_asm = GTK_BUTTON(gtk_builder_get_object(builder, "dbn_asm"));

    GtkButton *search_button = GTK_BUTTON(gtk_builder_get_object(builder, "search_button"));
    /*entries*/
    ndc = GTK_ENTRY(gtk_builder_get_object(builder, "ndc"));
    psw = GTK_ENTRY(gtk_builder_get_object(builder, "psw"));

    input_greed = GTK_ENTRY(gtk_builder_get_object(builder, "inpt_greed"));
    output_greed = GTK_ENTRY(gtk_builder_get_object(builder, "outpt_greed"));

    input_DBN = GTK_ENTRY(gtk_builder_get_object(builder, "inpt_DBN"));
    output_DBN = GTK_ENTRY(gtk_builder_get_object(builder, "outpt_DBN"));
    k = GTK_ENTRY(gtk_builder_get_object(builder, "k"));

    adn_sea = GTK_ENTRY(gtk_builder_get_object(builder, "adn_sea"));
    virus_sea = GTK_ENTRY(gtk_builder_get_object(builder, "virus_sea"));

    /*CONNCET BUTTON TO STUFF*/
    g_signal_connect(button_ass, "clicked", G_CALLBACK(show_ass_win), NULL);
    g_signal_connect(button_sea, "clicked", G_CALLBACK(show_search_win), NULL);
    g_signal_connect(button_quit, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(button_dbn, "clicked", G_CALLBACK(show_dbn_win), NULL);
    g_signal_connect(button_greed, "clicked", G_CALLBACK(show_greed_win),NULL);

    g_signal_connect(button_conn, "clicked", G_CALLBACK(show_main_win), NULL);

    g_signal_connect(button_greed_asm, "clicked", G_CALLBACK(ASSEMBLAGE_GREED), NULL);
    // g_signal_connect(button_dbn_asm, "clicked", G_CALLBACK(ASSEMBLAGE_DBN), NULL);
    /*de bruijn graphs soon*/
    //g_signal_connect(search_button, "clicked", G_CALLBACK(RECHERCHE),NULL);

    gtk_widget_show(authent_win);

    gtk_main();

    return 0;
}
