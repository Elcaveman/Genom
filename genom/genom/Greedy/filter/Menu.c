#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>


void printfff(char* c, int v){
    int i;
    for (i=0; i< strlen(c); i++){
        putchar(c[i]);
        Sleep(v);
    }
}

void welcome(){
    char espace[] = "          ";
    printf("    #                                                                                                    #####                                            \n");
    printf("   # #    ####   ####  ###### #    # #####  #        ##    ####  ######          #####  ######          #     # ###### #    #  ####  #    # ######  ####\n");
    printf("  #   #  #      #      #      ##  ## #    # #       #  #  #    # #               #    # #               #       #      ##   # #    # ##  ## #      #\n");
    printf(" #     #  ####   ####  #####  # ## # #####  #      #    # #      #####           #    # #####           #  #### #####  # #  # #    # # ## # #####   ####\n");
    printf(" #######      #      # #      #    # #    # #      ###### #  ### #               #    # #               #     # #      #  # # #    # #    # #           #\n");
    printf(" #     # #    # #    # #      #    # #    # #      #    # #    # #               #    # #               #     # #      #   ## #    # #    # #      #    #\n");
    printf(" #     #  ####   ####  ###### #    # #####  ###### #    #  ####  ######          #####  ######           #####  ###### #    #  ####  #    # ######  ####\n");
    printf("\n");printf("\n");printf("\n");printf("\n");

    printf("%s%s%s%s",espace,espace,espace,espace);
    int v = 65;
    printfff("PROJET C \n", v);
    printf("%s%s%s%s%s",espace,espace,espace,espace,espace);
    printfff("SEQUENCAGE : ASSEMBLAGE DE GENOMES \n\n", v);
    printf("%s%s%s%s%s",espace,espace,espace,espace,espace);
    printfff("REALISE PAR :\n", v);
    printf("%s%s%s%s%s",espace,espace,espace,espace,espace);
    printfff("EL BAHAOUI OUSSAMA\n", v);
    printf("%s%s%s%s%s",espace,espace,espace,espace,espace);
    printfff("BOUCHANE AMAL \n", v);
    printf("%s%s%s%s%s",espace,espace,espace,espace,espace);
    printfff("ENCADRANT : Mr A. EL HASSOUNY", v);

    printf("\n\n%s%s%s%sAppuyez sur entree pour continuer... ",espace,espace,espace,espace);

    getchar();

}

void menuText(){
    char espace[] = "          ";
    printf("    #                                                                                                    #####                                            \n");
    printf("   # #    ####   ####  ###### #    # #####  #        ##    ####  ######          #####  ######          #     # ###### #    #  ####  #    # ######  ####\n");
    printf("  #   #  #      #      #      ##  ## #    # #       #  #  #    # #               #    # #               #       #      ##   # #    # ##  ## #      #\n");
    printf(" #     #  ####   ####  #####  # ## # #####  #      #    # #      #####           #    # #####           #  #### #####  # #  # #    # # ## # #####   ####\n");
    printf(" #######      #      # #      #    # #    # #      ###### #  ### #               #    # #               #     # #      #  # # #    # #    # #           #\n");
    printf(" #     # #    # #    # #      #    # #    # #      #    # #    # #               #    # #               #     # #      #   ## #    # #    # #      #    #\n");
    printf(" #     #  ####   ####  ###### #    # #####  ###### #    #  ####  ######          #####  ######           #####  ###### #    #  ####  #    # ######  ####\n");
    printf("\n");printf("\n");printf("\n");printf("\n");
    printf("%s%s%s------------------------------------------------------------------------------------\n",espace,espace,espace);
    printf("%s%s%s----------------------------M E N U  P R I N C I P A L E----------------------------\n",espace,espace,espace);
    printf("%s%s%s------------------------------------------------------------------------------------\n",espace,espace,espace);

    printf("%s%s%s%s%sChoisissez une operation: \n",espace,espace,espace,espace,espace);
    printf("%s%s%s%s%s1 - Assemblage\n",espace,espace,espace,espace,espace);
    printf("%s%s%s%s%s2 - Recherche\n",espace,espace,espace,espace,espace);
    printf("%s%s%s%s%s3 - Quitter\n",espace,espace,espace,espace,espace);
}

void menu(){
    menuText();
    int choix = 99;
    char SS[20000];
    char espace[] = "          ";
    int assemblageFait = 0;
    while(1==1){
        printf("\n%s%s%sChoisir la fonction a appliquer  !    ", espace,espace,espace);
        scanf("%d", &choix);

        switch(choix){
            case 1: {
                Assemblage(SS);
                assemblageFait = 1;
                break;
            }
            case 2 : {
                printf("\n%s%s%s%s%s2-1- Rechercher dans un fichier\n", espace,espace, espace,espace,espace);
                printf("%s%s%s%s%s2-2- Rechercher dans la sequence originale\n", espace, espace,espace,espace,espace);
                printf("%s%s%s%s%s2-3- Retour au menu principal\n", espace,espace,espace, espace,espace);
                int _choix = 1;
                printf("%s%s%s%s%s", espace,espace,espace, espace,espace);
                scanf("%d", &_choix);
                while(_choix==1 || _choix==2){
                    if (_choix==1){
                        rechercheFichier();
                        printf("\n");
                        system("pause");
                        break;
                    }
                    if (_choix==2){
                        if (assemblageFait == 0){
                            printf("%s%s%s%s%sDesole, il faut faire le sequencage en premier\n",espace,espace,espace, espace,espace);
                            system("pause");
                            break;
                        }
                        rechercheSS(SS);
                        printf("\n");
                        system("pause");
                        break;
                    }
                }
                break;
            }
            case 3 :  exit(0);
            default : break;
        }
        system("cls");
        menuText();
    }
}

