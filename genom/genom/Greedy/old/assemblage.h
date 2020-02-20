
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <gtk/gtk.h>

#define FQ_FILE_PATH "C:/Users/HP/Desktop/genom/genom/Data/ads1_week4_reads.fq"
#define OUTPUT_PATH  "C:/Users/HP/Desktop/genom/genom/Data/result ADN.txt"
#define VIRUS_FILE_PATH "C:/Users/HP/Desktop/genom/genom/Data/virus db.txt"
#define VIRUS_SCAN_RESULT "C:/Users/HP/Desktop/genom/genom/Data/scan result.txt"


typedef struct Element{
    char ligne[101];
    struct Element *NEXT;
}Element;

typedef struct Liste{
    struct Element *head;
}Liste;

typedef struct Tuple{
    char gauche[101];
    char droite[101];
    struct Tuple *NEXT;
}Tuple;

typedef struct Dictionnaire{
    struct Tuple *head;
}Dictionnaire;

Liste *init_liste();
Dictionnaire *init_dico();
void insert_liste(Liste *liste, char new_ligne[]);
void insert_dico(Dictionnaire *dico, char gauche[], char droite[]);

void afficher_liste(Liste *liste);//pour débeugage
void afficherDico(Dictionnaire *dico);//pour débeugage

int recherche(Liste* liste, char ligne[]);
void lire_sequence(char ligne[],FILE* fichier);
Liste* convertion_fichier_liste(char nomFichier[]);
int len_liste(Liste *liste);
void suprimer_element(Liste *liste, char ligne[]);
int taille_dico(Dictionnaire *dico);

int overlap(char chaine1[] , char chaine2[] , int min , int concatenate);
Dictionnaire *permutations(Liste* liste);
int get_maximum_overlap(Liste* liste, Dictionnaire* dico, int k, char read_a[], char read_b[]);
void enregister_superstring(char nomFichier[],Liste* liste);
void greedy_setcover(char nomFichier[] ,Liste* liste, int k, Dictionnaire *dico);

void ASSEMBLAGE();

