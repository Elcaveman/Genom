#include "assemblage.h"

Liste *init_liste(){
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    strcpy(element->ligne, "");
    element->NEXT = NULL;
    liste->head = element;
    return liste;
}

Dictionnaire *init_dico(){
    Dictionnaire *dico = malloc(sizeof(*dico));
    Tuple *tuple = malloc(sizeof(*tuple));

    strcpy(tuple->gauche, "");
    strcpy(tuple->droite, "");
    tuple->NEXT = NULL;
    dico->head = tuple;

    return dico;
}

void insert_liste(Liste *liste, char new_ligne[]){
    /* New element */
    Element *nouveau = malloc(sizeof(*nouveau));

    strcpy(nouveau->ligne,new_ligne);

    /* Insert au debut de la liste */
    nouveau->NEXT = liste->head;
    liste->head = nouveau;
}

void insert_dico(Dictionnaire *dico, char gauche[], char droite[]){
    /* creates new element */
    Tuple *nouveau = malloc(sizeof(*nouveau));
    Tuple *actuel = dico->head;
    int r = 0;
    while (actuel != NULL){
        /* il se peut que actuel->droit == gauche donc il faut le tester aussi*/
        if (strcmp(gauche,droite)==0||(strcmp(actuel->droite, droite)==0 && (strcmp(actuel->gauche, gauche)==0 ))||((strcmp(actuel->droite, gauche)==0)  && (strcmp(actuel->gauche, droite)==0))){
            r = 1;
        }
        actuel = actuel->NEXT;
    }
    if (r==0){
        strcpy(nouveau->droite, droite);
        strcpy(nouveau->gauche, gauche);

        /* Insert element au début de la liste */
        nouveau->NEXT = dico->head;
        dico->head = nouveau;
    }
}

void afficher_liste(Liste *liste){

    Element *actuel = liste->head;

    while (actuel != NULL){
        Element *actuel2 = liste->head;
        actuel = actuel->NEXT;
    }
}

void afficher_dico(Dictionnaire *dico){

    Tuple *actuel = dico->head;

    while (actuel != NULL){
        actuel = actuel->NEXT;
    }
}

int recherche_liste(Liste* liste, char ligne[]){
    Element *current = liste->head;

    while(current!=NULL && strcmp(current->ligne,ligne)!=0){
          current = current->NEXT;
    }

    if(current!=NULL){
        /* l'element existe dans la liste-> return 1*/
        return 1;
    }
    return 0;
}

void lire_sequence(char ligne[],FILE* fichier){
    char garbage[100];char ok[100];
    fscanf(fichier , "%s",ok);
    fscanf(fichier , "%s",ligne);
    fscanf(fichier , "%s",garbage);
    fscanf(fichier , "%s",garbage);
}

Liste* convertion_fichier_liste(char nomFichier[]){
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");
    /* to test if input file exists or not*/
    Liste* liste = init_liste();
    if (fichier==NULL) return NULL;
    else{
        int i = 0;
        char ligne[101]="";
        /*pour que les char ne sois pas initialisé au hazard*/
        while(i<10){
            lire_sequence(ligne,fichier);
            if (recherche_liste(liste, ligne)==0){
                insert_liste(liste, ligne);
            }
            i++;
        }
    }
    fclose(fichier);
    return liste;
}

int len_liste(Liste *liste){
        Element* actuel = liste->head;
        int N = -1;/* car la liste n'est pas initialisée en NULL*/

        while(actuel!=NULL){
            N++;
            actuel = actuel->NEXT;
        }
        return N;
}

int supprimer(Liste *liste, char ligne[]) {
	Element *current = liste->head;
	Element *precedant;
	int i,j;
	i = len_liste(liste);
	while (current->NEXT != NULL) {
		precedant = current;
		current = current->NEXT;
		if (!strcmp(current->ligne, ligne)) {
			precedant->NEXT = current->NEXT;
			free(current);
		}
	}
	j=len_liste(liste);
	return (i-j);
}
void suprimer_element(Liste *liste, char ligne[]) {
	Element *current = liste->head;
	Element *Previous;
	while (current->NEXT != NULL) {
		Previous = current;
		current = current->NEXT;
		if (strcmp(current->ligne, ligne)==0){
			Previous->NEXT = current->NEXT;/*skips the element*/
			free(current);/*suprimer*/
		}
	}
}

int taille_dico(Dictionnaire *dico){
        Tuple* actuel = dico->head;
        int N = -1;/* de meme */

        while(actuel!=NULL){
            N++;
            actuel = actuel->NEXT;
        }
        return N;
}


int overlap(char chaine1[] , char chaine2[] , int min , int concatenate){
    /* if concatenate ==0 on ne fait pas la concaténation*/
    /*PART1: GET OVERLAP */
    int len_chaine1 = strlen(chaine1);
    int len_chaine2 = strlen(chaine2);

    int overlap = len_chaine1;
    int cursor_chaine1 = 0;
    int sliding_idx = 0;

    while (sliding_idx+cursor_chaine1 != len_chaine1){

        if (chaine1[sliding_idx+cursor_chaine1] == chaine2[sliding_idx] ){
            sliding_idx +=1;
        }
        else{
            cursor_chaine1 +=1;
            overlap -=1;
        }
    }
    /*PART2: CONCATENATE THE TWO STRINGS*/
    if (concatenate)
    {    int cost = len_chaine2 - overlap;
        char chaine_de_sauvegarde[cost];
        for (int i=0 ; i<cost ; i++){
            chaine_de_sauvegarde[i] = chaine2[overlap+i];
        }
        // La concatènation est faite
        strcat(chaine1 , chaine_de_sauvegarde);}
    if (overlap<min) return 0;
    else return overlap;

}

Dictionnaire *permutations(Liste* liste){
    int i, j, len;
    len = len_liste(liste);
    Dictionnaire* dico = init_dico();
    Element* actuel_i = liste->head;
    for (i = 0; i< len; i++){
        Element* actuel_j = liste->head;
        for (j=0; j<len; j++){
            if (i!=j){
                insert_dico(dico, actuel_i->ligne, actuel_j->ligne);
                actuel_j = actuel_j->NEXT;
            }
        }
        actuel_i = actuel_i->NEXT;
    }
    return dico;
}

int get_maximum_overlap(Liste* liste, Dictionnaire* dico, int k, char read_a[], char read_b[]){
    int overlap_len=0;
    int best_olen = 0;
    Tuple* actuel = dico->head;
    while(actuel!=NULL){
        overlap_len = overlap(actuel->gauche, actuel->droite, k ,0);
        if (overlap_len > best_olen){
            best_olen = overlap_len;
            strcpy(read_a, actuel->gauche);
            strcpy(read_b, actuel->droite);
        }
        actuel = actuel->NEXT;
    }

    return best_olen;
    }

void enregister_superstring(char nomFichier[],Liste* liste){
    FILE* fichier = fopen(nomFichier, "w");
    Element* read = liste->head;
    while(read!=NULL){
        read = read->NEXT;
    }
    fclose(fichier);
}

void greedy_setcover(char nomFichier[] ,Liste* liste, int k, Dictionnaire *dico){
    char read_a[101];
    char read_b[101];
    int overlap_len = get_maximum_overlap(liste, dico, k, read_a, read_b);
    while (overlap_len > 0){
        supprimer(liste, read_a);
        supprimer(liste, read_b);
 
        overlap(read_a,read_b,k,1);
        insert_liste(liste, read_a);
        overlap_len = get_maximum_overlap(liste, dico, k, read_a, read_b);
    }
    enregister_superstring(nomFichier,liste);
}

void ASSEMBLAGE(){

    Liste* listeDesSequences = NULL;
    listeDesSequences = convertion_fichier_liste(FQ_FILE_PATH);

    if (listeDesSequences==NULL){
        printf("\nImpossible de charger le fichier");
    }
    Dictionnaire* dico = permutations(listeDesSequences);
    greedy_setcover(OUTPUT_PATH,listeDesSequences, 0, dico);
}

int main(){
    ASSEMBLAGE();
}
