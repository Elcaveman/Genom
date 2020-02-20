#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Recherche.h"

int __find(char sub[], char _string[], int debut){
    int i,j;
    for (i=debut; i<(100 - strlen(sub)+1); i++){
        j  = 0;
        while(j<strlen(sub)+1){
            if (sub[j]!=_string[i+j]) break;
            j++;
        }
        if (j==strlen(sub)) return i;
    }
    return -1;
}

int isRead(char ligne[]){ //return 1 if it's a read
    int i = 0;
    if (strlen(ligne)>100) return 0;
    strcpy(ligne, strupr(ligne));
    while(i<strlen(ligne)){
        if (ligne[i]!='A' && ligne[i]!='C' && ligne[i]!='G' && ligne[i]!='T'){
            return 0;
        }
        i++;
    }
    return 1;
}

int fileEmpty(char nomFichier[]){ //return 1 if empty
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier==NULL){
        fclose(fichier);
        return 1;
    }
    fclose(fichier);
    return 0;
}

void _rechercheFichier(char nomFichier[], char souche[]){
    char espace[] = "          ";
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");
    int i = 0;
    char ligne[101]="";
    while(i<1881){
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        if (_find(souche, ligne,0)!=-1){
            printf("%s%sLa souche existe dans la collection des chaines!",espace,espace);
            return ;
        }
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        fgets(ligne, 100, fichier);
        i++;
    }
    printf("%s%sLa souche n'existe pas dans la collection des chaines!",espace,espace);
    fclose(fichier);
}

void rechercheFichier(){
    char espace[] = "          ";
    char souche[2000];
    char nomFichier[100];

    printf("%s%s%sEntrez la souche : ",espace,espace,espace);
    scanf("%s", souche);
    while(isRead(souche)==0){
        printf("\n%s%s%sMotif invalide !",espace,espace,espace);
        printf("\n%s%s%sEntrez une autre souche ",espace,espace,espace);
        scanf("%s", souche);
    }

    printf("\n %s%s%sEntrer le nom du fichier : ",espace,espace,espace);
    scanf("%s", nomFichier);
    while(fileEmpty(nomFichier)==1){
        printf("\n%s%s%sFichier invalide !",espace,espace,espace);
        printf("\n%s%s%sEntrer le nom d'un autre fichier / 0 pour quitter",espace,espace,espace);
        scanf("%s", nomFichier);
        if (strcmp("0", nomFichier)==0) break;
    }

    if (strcmp("0", nomFichier)!=0) _rechercheFichier(nomFichier, souche);
}

void _rechercheSS(char souche[], char SS[]){
    char espace[] = "          ";
    if (_find(souche, SS, 0)==(-1)){
        printf("%s%s%sLe motif n'existe pas dans la Chaine originale !",espace,espace,espace);
    }
    else{
        printf("%s%s%sLe motif existe dans la souche originale",espace,espace,espace);
    }
}

void rechercheSS(char SS[]){
    char souche[2000];
    char espace[] = "          ";
    printf("%s%s%sEntrez la souche : ",espace,espace,espace);
    scanf("%s", souche);
    while(isRead(souche)==0){
        printf("\n%s%s%sMotif invalide !",espace,espace,espace);
        printf("\n%s%s%sEntrez une autre souche ",espace,espace,espace);
        scanf("%s", souche);
    }

    _rechercheSS(souche, SS);
}

