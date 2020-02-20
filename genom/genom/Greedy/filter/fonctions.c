#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "declare.h"
#define max(a,b) a<b? b:a
#define min(a,b) a>b? b:a

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    strcpy(element->ligne, "");
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

Dictionnaire *initialisationD()
{
    Dictionnaire *dico = malloc(sizeof(*dico));
    Tuple *tuple = malloc(sizeof(*tuple));

    strcpy(tuple->gauche, "");
    strcpy(tuple->droite, "");
    tuple->suivant = NULL;
    dico->premier = tuple;

    return dico;
}

void insertion(Liste *liste, char nvLigne[])
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));

    strcpy(nouveau->ligne,nvLigne);

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void insertionD(Dictionnaire *dico, char gauche[], char droite[])
{
    /* Création du nouvel élément */
    Tuple *nouveau = malloc(sizeof(*nouveau));
    Tuple *actuel = dico->premier;
    int r = 0;
    while (actuel != NULL)
    {
        if ((strcmp(actuel->droite, droite)==0 && (strcmp(actuel->gauche, gauche)==0 ))||((strcmp(actuel->droite, gauche)==0)  && (strcmp(actuel->gauche, droite)==0)))
        {
            r = 1;
        }
        actuel = actuel->suivant;
    }
    if (r==0)
    {
        strcpy(nouveau->droite, droite);
        strcpy(nouveau->gauche, gauche);

        /* Insertion de l'élément au début de la liste */
        nouveau->suivant = dico->premier;
        dico->premier = nouveau;
    }
}

void afficherListe(Liste *liste)
{

    Element *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%s\n", actuel->ligne);
        actuel = actuel->suivant;
    }
}

void afficherDico(Dictionnaire *dico)
{

    Tuple *actuel = dico->premier;

    while (actuel != NULL)
    {
        printf("(%s , %s)\n", actuel->gauche, actuel->droite);
        actuel = actuel->suivant;
    }
}

int recherche(Liste* liste, char ligne[])
{
    Element *current = liste->premier;

    while(current!=NULL && strcmp(current->ligne,ligne)!=0)
    {
        current = current->suivant;
    }

    if(current!=NULL)
    {
        return 1;
    }
    return 0;
}

Liste* chargement(char* nomFichier[])
{
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");
    Liste* liste = initialisation();
    if (fichier==NULL) return NULL;
    else
    {
        int i = 0;
        char ligne[101]="";
        while(i<10)
        {
            fgets(ligne, 100, fichier);
            fgets(ligne, 100, fichier);
            if (recherche(liste, ligne)==0)
            {
                insertion(liste, ligne);
            }
            fgets(ligne, 100, fichier);
            fgets(ligne, 100, fichier);
            fgets(ligne, 100, fichier);
            fgets(ligne, 100, fichier);
            i++;
        }
    }
    fclose(fichier);
    return liste;
}

int tailleListe(Liste *liste)
{
    Element* actuel = liste->premier;
    int N = -1;

    while(actuel!=NULL)
    {
        N++;
        actuel = actuel->suivant;
    }
    return N;
}

int supprimer(Liste *liste, char ligne[])
{
    Element *current = liste->premier;
    Element *precedant;
    int i,j;
    i = tailleListe(liste);
    while (current->suivant != NULL)
    {
        precedant = current;
        current = current->suivant;
        if (!strcmp(current->ligne, ligne))
        {
            precedant->suivant = current->suivant;
            free(current);
        }
    }
    j=tailleListe(liste);
    return (i-j);
}

int tailleDico(Dictionnaire *dico)
{
    Tuple* actuel = dico->premier;
    int N = -1;

    while(actuel!=NULL)
    {
        N++;
        actuel = actuel->suivant;
    }
    return N;
}

int find(char sub[], char string[], int debut)
{
    int i,j;
    for (i=debut; i<(100 - strlen(sub)+1); i++)
    {
        j  = 0;
        while(j<strlen(sub)+1)
        {
            if (sub[j]!=string[i+j]) break;
            j++;
        }
        if (j==strlen(sub)) return i;
    }
    return -1;
}

char* subString(char chaine[], int debut, int fin)
{
    int i;
    char sub[101];
    for(i = 0; i<fin-debut+1; i++)
    {
        sub[i] = chaine[i+debut];
    }
    sub[fin-debut+1] = '\0';

    return sub;
} //strcpy a faire apres

int overlap(char a[], char b[], int min_length)
{
    int start = 0;
    while (1==1)
    {
        char r[min_length] ;
        strcpy(r, subString(b,0,min_length-1));
        start = find(r,a, start);
        if (start ==-1) return 0;
        char s[101];
        strcpy(s, subString(a,start, strlen(a)-1));
        if (find(s, b, 0 )==0) return strlen(a)-start;
        start +=1;
    }
}

Dictionnaire *permutations(Liste* liste)
{
    int i, j, len;
    len = tailleListe(liste);
    Dictionnaire* dico = initialisationD();
    Element* actuel_i = liste->premier;
    for (i = 0; i< len; i++)
    {
        j = 0;
        Element* actuel_j = liste->premier;
        while(j < len)
        {
            insertionD(dico, actuel_i->ligne, actuel_j->ligne);
            actuel_j = actuel_j->suivant;
            j++;
        }
        actuel_i = actuel_i->suivant;
    }
    return dico;
}

Dictionnaire *k_permutations(Liste* liste, int k)
{

    int i, j, len;
    len = tailleListe(liste);
    Dictionnaire* dico = initialisationD();
    Element* read = liste->premier;
    for (i = 0; i< len; i++)
    {
        for (j = 0; j< strlen(read->ligne) -k +1; j++)
        {
            char r[101];
            strcpy(r, subString(read->ligne, j, j+k));
            insertionD(dico, r, read->ligne);
            printf("%d",i);
        }
        read = read->suivant;
    }
    return dico;
}

Liste* valeurs(char cle[], Dictionnaire* dico)
{
    Liste* liste_valeurs = initialisation();
    Tuple* actuel = dico->premier;
    while(actuel!=NULL)
    {
        printf("%d\n",strlen(actuel->gauche));
        if (strcmp(actuel->gauche, cle)==0)
        {
            insertion(liste_valeurs, actuel->droite);
        }
        actuel = actuel->suivant;
    }
    return liste_valeurs;
}

int pick_maximal_overlap(Liste* liste, Dictionnaire* dico, int k, char reada[], char readb[])
{
    int olen=0;
    int best_olen = 0;
    Tuple* actuel = dico->premier;
    while(actuel!=NULL)
    {
        olen = overlap(actuel->gauche, actuel->droite, k);
        if (olen > best_olen)
        {
            best_olen = olen;
            strcpy(reada, actuel->gauche);
            strcpy(readb, actuel->droite);
        }
        actuel = actuel->suivant;
    }
    return best_olen;
//    int olen = 0;
//    int best_olen = 0;
//    Element* r = liste->premier;
//    while(r!=NULL){
//        char s[101];
//        strcpy(s, subString(r, strlen(r)-k, strlen(r)-1));
//        Tuple* actuel = dico->premier;
//        while(actuel!=NULL){
//            if (strcmp(s,actuel->droite)==0){
//                if (strcmp(r->ligne,actuel->droite)!=0){
//                    olen = overlap(r->ligne, actuel->droite,k);
//                    if (olen > best_olen){
//                        strcpy(reada, r->ligne);
//                        strcpy(readb,actuel->droite);
//                        best_olen = olen;
//                    }
//                }
//            }
//            actuel = actuel->suivant;
//        }
//        r = r->suivant;
//    }
//    return best_olen;
}

char *join(Liste* liste)
{
    char superString[20000];
    Element* read = liste->premier;
    while(read!=NULL)
    {
        strcat(superString, read->ligne);
        read = read->suivant;
    }

    return superString;
}

char* greedy_scs(Liste* liste, int k, Dictionnaire *dico)
{
    char read_a[101];
    char read_b[101];
    int olen = pick_maximal_overlap(liste, dico, k, read_a, read_b);
    while (olen > 0)
    {
        supprimer(liste, read_a);
        supprimer(liste, read_b);
        char s[101];
        strcpy(s, subString(read_b, olen, strlen(read_b)-1));
        strcat(read_a, s);
        insertion(liste, read_a);
        olen = pick_maximal_overlap(liste, dico, k, read_a, read_b);
    }
    return join(liste);
}

void enregistrerSequence(char nomFichier[], char SS[])
{
    FILE* fichier = fopen(nomFichier, "w+");

    fprintf(fichier, SS);

    printf("\nEnregistre avec succes");

    fclose(fichier);
}

void Assemblage(char* SS[])
{
    char nomFichier[200];
    printf("Entrer le nom du fichier a sequencer !");
    scanf("%s", nomFichier);

    Liste* listeDesSequences = NULL;
    listeDesSequences = chargement(nomFichier);

    if (listeDesSequences==NULL)
    {
        printf("\nImpossible de charger le fichier");
        return;
    }

    Dictionnaire* dico = permutations(listeDesSequences);
    printf("\nDebut du sequencage ... ");
    char superString[20000];
    strcpy(superString, greedy_scs(listeDesSequences, 80, dico));

    printf("\nSequencage terminee avec succes!");

    printf("\n\nEntrer le nom du fichier ou enregistrer la sequence originale : ");
    char nvFichier[200];
    scanf("%s", nvFichier);

    enregistrerSequence(nvFichier, superString);

    strcpy(SS, superString);
}

// Fonctions pour Rechercher
int isRead(char ligne[])  //return 1 if it's a read
{
    int i = 0;
    if (strlen(ligne)>100) return 0;
    strcpy(ligne, strupr(ligne));
    while(i<strlen(ligne))
    {
        if (ligne[i]!='A' && ligne[i]!='C' && ligne[i]!='G' && ligne[i]!='T')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int fileEmpty(char nomFichier[])  //return 1 if empty
{
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier==NULL)
    {
        fclose(fichier);
        return 1;
    }
    fclose(fichier);
    return 0;
}

void _rechercheFichier(char nomFichier[], char souche[])
{
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");
    int i = 0;
    char ligne[101]="";
    while(i<1881)
    {
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        if (find(souche, ligne,0)!=-1)
        {
            printf("La souche existe dans la collection des chaines!");
            return;
        }
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        i++;
    }
    printf("La souche n'existe pas dans la collection des chaines!");
    fclose(nomFichier);
}

void rechercheFichier()
{
    char souche[2000];
    char nomFichier[100];

    printf("Entrez la souche : ");
    scanf("%s", souche);
    while(isRead(souche)==0)
    {
        printf("\nMotif invalide !");
        printf("\nEntrez une autre souche ");
        scanf("%s", souche);
    }

    printf("\n Entrer le nom du fichier : ");
    scanf("%s", nomFichier);
    while(fileEmpty(nomFichier)==1)
    {
        printf("\nFichier invalide !");
        printf("\nEntrer le nom d'un autre fichier ");
        scanf("%s", nomFichier);
    }

    _rechercheFichier(nomFichier, souche);
}

void _rechercheSS(char souche[], char SS[])
{
    if (find(souche, SS, 0)==(-1))
    {
        printf("Le motif n'existe pas dans la Chaine originale !");
    }
    else
    {
        printf("Le motif existe dans la souche originale");
    }
}

void rechercheSS(char SS[])
{
    char souche[2000];

    printf("Entrez la souche : ");
    scanf("%s", souche);
    while(isRead(souche)==0)
    {
        printf("\nMotif invalide !");
        printf("\nEntrez une autre souche ");
        scanf("%s", souche);
    }

    _rechercheSS(souche, SS);
}

void menuText()
{
    printf("------------------------------------------------------------------------------------\n");
    printf("----------------------------M E N U  P R I N C I P A L E----------------------------\n");
    printf("------------------------------------------------------------------------------------\n");

    printf("Choisissez une operation: \n");
    printf("1 - Assemblage\n");
    printf("2 - Recherche\n");
    printf("3 - Quitter\n");
}

void menu()
{
    menuText();
    int choix = 1;
    scanf("%d", &choix);
    char SS[20000];
    while(choix>0 && choix <3)
    {
        printf("\nChoisir la fonction a appliquer  !\n");
        scanf("%d", &choix);
        int assemblageFait = 0;
        switch(choix)
        {
        case 1:
        {
            Assemblage(SS);
            assemblageFait = 1;
            break;
        }
        case 2 :
        {
            printf("2-1- Rechercher dans un fichier\n");
            printf("2-2- Rechercher dans la sequence originale\n");
            int _choix = 1;
            scanf("%d", &_choix);
            while(_choix==1 || _choix==2)
            {
                if (_choix==1)
                {
                    rechercheFichier();
                    break;
                }
                if (_choix==2)
                {
                    if (assemblageFait == 0)
                    {
                        printf("Desole, il faut faire le sequencage en premier");
                        break;
                    }
                    rechercheSS(SS);
                    break;
                }
            }
            break;
        }
        }
    }
}
