#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assemblage.h"

Liste *initialisation_liste(){
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    strcpy(element->ligne, "");
    element->NEXT = NULL;
    liste->HEAD = element;

    return liste;
}

Dictionnaire *initialisation_dico(){
    Dictionnaire *dico = malloc(sizeof(*dico));
    Tuple *tuple = malloc(sizeof(*tuple));

    strcpy(tuple->gauche, "");
    strcpy(tuple->droite, "");
    tuple->NEXT = NULL;
    dico->HEAD = tuple;

    return dico;
}

void insertion_liste(Liste *liste, char nvLigne[]){
    /* Cr�ation du nouvel �l�ment */
    Element *nouveau = malloc(sizeof(*nouveau));

    strcpy(nouveau->ligne,nvLigne);

    /* Insertion de l'�l�ment au d�but de la liste */
    nouveau->NEXT = liste->HEAD;
    liste->HEAD = nouveau;
}

void insertion_dico(Dictionnaire *dico, char gauche[], char droite[]){
    /* Cr�ation du nouvel �l�ment */
    Tuple *nouveau = malloc(sizeof(*nouveau));
    Tuple *actuel = dico->HEAD;
    int r = 0;
    while (actuel != NULL){
        if ((gauche, droite)==0||(strcmp(actuel->droite, droite)==0 && (strcmp(actuel->gauche, gauche)==0 ))||((strcmp(actuel->droite, gauche)==0)  && (strcmp(actuel->gauche, droite)==0))){
            r = 1;
        }
        actuel = actuel->NEXT;
    }
    if (r==0){
        strcpy(nouveau->droite, droite);
        strcpy(nouveau->gauche, gauche);

        /* Insertion de l'�l�ment au d�but de la liste */
        nouveau->NEXT = dico->HEAD;
        dico->HEAD = nouveau;
    }
}

void afficher_liste(Liste *liste){

    Element *actuel = liste->HEAD;

    while (actuel != NULL){
        printf("%s\n", actuel->ligne);
        actuel = actuel->NEXT;
    }
}

void afficher_dico(Dictionnaire *dico){

    Tuple *actuel = dico->HEAD;

    while (actuel != NULL){
        printf("(%s , %s)\n", actuel->gauche, actuel->droite);
        actuel = actuel->NEXT;
    }
}

int recherche_liste(Liste* liste, char ligne[]){
    Element *current = liste->HEAD;

    while(current!=NULL && strcmp(current->ligne,ligne)!=0){
          current = current->NEXT;
    }

    if(current!=NULL){
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
Liste* chargement_input(char nomFichier[]){
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");
    Liste* liste = initialisation_liste();
    if (fichier==NULL) return NULL;
    else{
        int i = 0;
        char ligne[101]="";
        while(i<35){
            lire_sequence(ligne,fichier);
            if (recherche_liste(liste, ligne)==0){
                insertion_liste(liste, ligne);
            }
            
            i++;
        }
    }
    fclose(fichier);
    return liste;
}

int taille_liste(Liste *liste){
        Element* actuel = liste->HEAD;
        int N = -1;

        while(actuel!=NULL){
            N++;
            actuel = actuel->NEXT;
        }
        return N;
}

int supprimer(Liste *liste, char ligne[]) {
	Element *current = liste->HEAD;
	Element *precedant;
	int i,j;
	i = taille_liste(liste);
	while (current->NEXT != NULL) {
		precedant = current;
		current = current->NEXT;
		if (!strcmp(current->ligne, ligne)) {
			precedant->NEXT = current->NEXT;
			free(current);
		}
	}
	j=taille_liste(liste);
	return (i-j);
}

int taille_dico(Dictionnaire *dico){
        Tuple* actuel = dico->HEAD;
        int N = -1;

        while(actuel!=NULL){
            N++;
            actuel = actuel->NEXT;
        }
        return N;
}

int find_overlap_start(char substring[], char read[], int debut){
    int i,j;
    for (i=debut; i<(100 - strlen(substring)+1); i++){
        j  = 0;
        while(j<strlen(substring)+1){
            if (substring[j]!=read[i+j]) break;
            j++;
        }
        if (j==strlen(substring)) return i;
    }
    return -1;
}

char* subString(char chaine[], int debut, int fin){
    int i;
    char *sub = (char*)malloc(101*sizeof(char));
    for(i = 0; i<fin-debut+1; i++){
        sub[i] = chaine[i+debut];
    }
    sub[fin-debut+1] = '\0';

    return sub;
} //strcpy a faire apres

int overlap(char a[], char b[], int min_length){
    int start = 0;
    while (1==1){
        char r[min_length] ;
        strcpy(r, subString(b,0,min_length-1));
        start = find_overlap_start(r,a, start);
        if (start ==-1) return 0;
        char s[101];
        strcpy(s, subString(a,start, strlen(a)-1));
        if (find_overlap_start(s, b, 0 )==0) return strlen(a)-start;
        start +=1;
    }
}

Dictionnaire *permutations(Liste* liste){
    int i, j, len;
    len = taille_liste(liste);
    Dictionnaire* dico = initialisation_dico();
    Element* actuel_i = liste->HEAD;
    for (i = 0; i< len; i++){
        j = 0;
        Element* actuel_j = liste->HEAD;
        while(j < len){
            insertion_dico(dico, actuel_i->ligne, actuel_j->ligne);
            actuel_j = actuel_j->NEXT;
            j++;
        }
        actuel_i = actuel_i->NEXT;
    }
    return dico;
}

int overlap_maximale(Liste* liste, Dictionnaire* dico, int k, char reada[], char readb[]){
    int olen=0;
    int best_olen = 0;
    Tuple* actuel = dico->HEAD;
    while(actuel!=NULL){
        olen = overlap(actuel->gauche, actuel->droite, k);
        if (olen > best_olen){
            best_olen = olen;
            strcpy(reada, actuel->gauche);
            strcpy(readb, actuel->droite);
        }
        actuel = actuel->NEXT;
    }
    return best_olen;
}

char *join(Liste* liste){
    char* superString = (char*)malloc(20000*sizeof(char));
    Element* read = liste->HEAD;
    while(read!=NULL){
        strcat(superString, read->ligne);
        read = read->NEXT;
    }

    return superString;
}

char* greedy_setcover(Liste* liste, int k, Dictionnaire *dico){
    char read_a[101];
    char read_b[101];
    int olen = overlap_maximale(liste, dico, k, read_a, read_b);
    while (olen > 0){
        supprimer(liste, read_a);
        supprimer(liste, read_b);
        char s[101];
        strcpy(s, subString(read_b, olen, strlen(read_b)-1));
        strcat(read_a, s);
        insertion_liste(liste, read_a);
        olen = overlap_maximale(liste, dico, k, read_a, read_b);
    }
    return join(liste);
}

void sauvegarde_superstring(char nomFichier[], char SS[]){
    FILE* fichier = fopen(nomFichier, "w+");
    char espace[] ="          ";
    fprintf(fichier, SS);

    printf("\n%s%s%sEnregistre avec succes",espace,espace,espace);

    fclose(fichier);
}

void Assemblage_greed(){
    char espace[] ="          ";
    char nomFichier[200];
    printf("%s%s%sEntrer le nom du fichier a assembler !",espace,espace,espace);
    scanf("%s", nomFichier);

    Liste* listeDesSequences = NULL;
    listeDesSequences = chargement_input(nomFichier);

    if (listeDesSequences==NULL){
        printf("\n%s%s%sImpossible de charger le fichier",espace,espace,espace);
        system("pause");
        return;
    }

    Dictionnaire* dico = permutations(listeDesSequences);
    printf("\n%s%sAssemblage en cours... ",espace,espace);
    int cc=0;
    while(cc<1000000000){
            cc++;
    }
    char superString[20000];
    strcpy(superString, greedy_setcover(listeDesSequences, 80, dico));

    printf("\n%s%sAssemblage terminee avec succes!",espace,espace);

    printf("\n\n%s%sEntrer le nom du fichier ou enregistrer la sequence originale : ",espace,espace);

    char nvFichier[200];
    scanf("%s", nvFichier);

    sauvegarde_superstring(nvFichier, superString);
    printf("\n");
    system("pause");

}

int main(){
    Assemblage_greed();
    return 0;
}