#include<stdio.h>
#include<string.h>


char* __motDePasse(){
    char espace[] = "          ";
    char s;
    int c=0;//0 est le code ASCII de NULL
    int i=0;//i est l'emplacement du console
    char p[40];//p est le mot de passe saisi
    char cacher[40];//cacher est la chaine des étoiles qui cache le mot de passe
    printf("\n%s%s%s%sTaper votre mot de passe:",espace,espace,espace,espace);
    while(c!=13){//13 est le code ASCII de ENTRER
        s=getch();
        c=s;//prendre le code ASCII du caractère
        if(c!=13){
            if(c==8){//8 est le code ASCII de back space
                system("cls");
                if(i)
                i=i-1;
                cacher[i]='\0';
                printf("\n%s%s%s%sTaper votre mot de passe:",espace,espace,espace,espace);
                printf("%s",cacher);
            }
            else{
               p[i]=s;
               printf("*");
               cacher[i]='*';
               i=i+1;
            }
        }
        else{
          p[i]='\0';
        }
    }
    return(p);
}

int _motDePasse(char *c){
    char mdp1[] = "Admin987";
//    char mdp2[] = "ADNADN0";
//    char mdp3[] = "Utilisateur01";
    if ((strcmp(c, mdp1)==0)) return 1;
    return 0;
}

void motDePasse(){
    char espace[] = "          ";
    system("cls");
    printf("      #                                                                                                    #####                                            \n");
    printf("     # #    ####   ####  ###### #    # #####  #        ##    ####  ######          #####  ######          #     # ###### #    #  ####  #    # ######  ####\n");
    printf("    #   #  #      #      #      ##  ## #    # #       #  #  #    # #               #    # #               #       #      ##   # #    # ##  ## #      #\n");
    printf("   #     #  ####   ####  #####  # ## # #####  #      #    # #      #####           #    # #####           #  #### #####  # #  # #    # # ## # #####   ####\n");
    printf("   #######      #      # #      #    # #    # #      ###### #  ### #               #    # #               #     # #      #  # # #    # #    # #           #\n");
    printf("   #     # #    # #    # #      #    # #    # #      #    # #    # #               #    # #               #     # #      #   ## #    # #    # #      #    #\n");
    printf("   #     #  ####   ####  ###### #    # #####  ###### #    #  ####  ######          #####  ######           #####  ###### #    #  ####  #    # ######  ####\n");
    printf("\n");printf("\n");printf("\n");printf("\n");
    char *mdp = __motDePasse();
    while (_motDePasse(mdp)==0){
        system("cls");
        printf("      #                                                                                                    #####                                            \n");
    printf("     # #    ####   ####  ###### #    # #####  #        ##    ####  ######          #####  ######          #     # ###### #    #  ####  #    # ######  ####\n");
    printf("    #   #  #      #      #      ##  ## #    # #       #  #  #    # #               #    # #               #       #      ##   # #    # ##  ## #      #\n");
    printf("   #     #  ####   ####  #####  # ## # #####  #      #    # #      #####           #    # #####           #  #### #####  # #  # #    # # ## # #####   ####\n");
    printf("   #######      #      # #      #    # #    # #      ###### #  ### #               #    # #               #     # #      #  # # #    # #    # #           #\n");
    printf("   #     # #    # #    # #      #    # #    # #      #    # #    # #               #    # #               #     # #      #   ## #    # #    # #      #    #\n");
    printf("   #     #  ####   ####  ###### #    # #####  ###### #    #  ####  ######          #####  ######           #####  ###### #    #  ####  #    # ######  ####\n");
    printf("\n");printf("\n");printf("\n");printf("\n");
        printf("\n\n%s%s%s%sMot de passe incorrect! \n\n",espace,espace,espace,espace);
        mdp = __motDePasse();
    }
    system("cls");
}


