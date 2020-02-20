#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recherche.h"

void recherche_souche_super(char souche[], char super[] , int len_super){
    FILE* fich = fopen("motif.txt","w");
    int len_sub = strlen(souche);
    int j =0;
    for (int i=0; i<(len_super - len_sub+1); i++){
        j  = 0;
        while(j<len_sub+1){
            if (souche[j]!=super[i+j]) break;
            j++;
        }
        if (j==len_sub){
            printf("%s\n",souche);
            fprintf(fich,"%s\n",souche);
            break;
        }
    }
    fclose(fich);
}
int read_adn(char super_string[], char adn_file[]){

    FILE* adn = fopen(adn_file , "r");
    fscanf(adn,"%s",super_string);
    fclose(adn);

    return strlen(super_string);
}
void recherche(char adn_file[] , char virus_db[]){
    char souche[250];
    char super_string[20000];
    int len_super = read_adn(super_string , adn_file);
    // FILE* adn = fopen(OUTPUT_PATH , "r");
    // fscanf(adn,"%s",super_string);
    // fclose(adn);
    // free(adn);

    // int len_super = strlen(super_string);
    /*you can use FILE* fopen one time only*/
    FILE* viruses = fopen(virus_db,"r");

    while (fscanf(viruses,"%s\n",souche)!=EOF){
        recherche_souche_super(souche , super_string , len_super);
    }
    fclose(viruses);
}

// int main(){
//     recherche("adn.txt","virus.txt");
// }