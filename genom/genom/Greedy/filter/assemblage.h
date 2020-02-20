typedef struct Element{
    char ligne[101];
    struct Element *NEXT;
}Element;

typedef struct Liste{
    struct Element *HEAD;
}Liste;

typedef struct Tuple{
    char gauche[101];
    char droite[101];
    struct Tuple *NEXT;
}Tuple;

typedef struct Dictionnaire{
    struct Tuple *HEAD;
}Dictionnaire;

Liste *initialisation_liste();
Dictionnaire *initialisation_dico();
void insertion_liste(Liste *liste, char nvLigne[]);
void insertion_dico(Dictionnaire *dico, char gauche[], char droite[]);
void afficher_liste(Liste *liste);/*debeugage*/
void afficher_dico(Dictionnaire *dico);/*debeugage*/
int recherche_liste(Liste* liste, char ligne[]);
void lire_sequence(char ligne[],FILE* fichier);
Liste* chargement_input(char nomFichier[]);
int taille_liste(Liste *liste);
int supprimer(Liste *liste, char ligne[]);
int taille_dico(Dictionnaire *dico);
int find_overlap_start(char substring[], char read[], int debut);
char* subString(char chaine[], int debut, int fin);
int overlap(char a[], char b[], int min_length);
Dictionnaire *permutations(Liste* liste);

int overlap_maximale(Liste* liste, Dictionnaire* dico, int k, char reada[], char readb[]);
char *union_liste(Liste* liste);
char* greedy_setcover(Liste* liste, int k, Dictionnaire *dico);
void sauvegarde_superstring(char nomFichier[], char SS[]);
void Assemblage_greed();
