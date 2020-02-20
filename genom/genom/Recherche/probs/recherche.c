#include "recherche.h"
virus_list* init_virus_list(){
    virus_list *liste = malloc(sizeof(virus_list*));

    virus element;
    strcpy(element.virus_genome , "");
    strcpy(element.virus_name ,"");
    element.virus_len = 0;
    element.NEXT = NULL;

    liste->head = &element;

    return liste;
}


int make_virus_list(virus_list* list_virus){
    int max_len=0;
    FILE* virus_db = NULL;
    virus_db = fopen(VIRUS_FILE_PATH,"r");
    
    virus* list_head = list_virus->head;/*np here*/
    
    if(virus_db == NULL)printf("impossible d'ouvrir db");
    else
    {   
        char buffer[202];
        int i=0;
        virus vir;
        while (fgets(buffer,200, virus_db)!=NULL){
            
            if (i==0) {strcpy(vir.virus_name,buffer);continue;}
            if (i==1) {vir.virus_len = atoi(buffer);continue;}
            if (i==2) strcpy(vir.virus_genome,buffer);
            i = (i+1)%3;
            // if (max_len < list_head->virus_len) max_len = list_head->virus_len;
            printf("%s\n%d\n%s",vir.virus_name,vir.virus_len,vir.virus_genome);
            system("pause");
            list_head = &vir;
            
            list_head = list_head->NEXT;
    }
    list_head = NULL;/*last one is null*/
    return max_len; /*utile*/
    }
    
   
}

virus_list* VIRUS_SCAN(){
    virus_list* list_virus = init_virus_list();
    
    int VIRUS_MAX_LEN = make_virus_list(list_virus);

    virus_list* virus_found = init_virus_list();

    virus* virus_found_head = virus_found->head;

    FILE* virus_scan_result = fopen(VIRUS_SCAN_RESULT,"w");
    FILE* genome = fopen(OUTPUT_PATH,"r");

    long v_position = 0;/*the start position of the "virus"*/
    char* adn_segment = MALLOC(char,VIRUS_MAX_LEN);

    while(fgets(adn_segment,VIRUS_MAX_LEN,genome)!=NULL){ 
        /* fgets reads line till it finds a \n or a set number of bytes*/
        /* returns NULL if the reading was unsuccessefull*/
        virus* list_head = list_virus->head;
        
        while (list_head!=NULL){
            int len = list_head->virus_len;
            if (strncmp(adn_segment , list_head->virus.virus_genome , len) ==0 ){
                if (virus_found->virus_len < len ){
                    strcpy(virus_found->virus_genome, list_head->virus_genome);
                    virus_found->virus_len = list_head->virus_len;
                    strcyp(virus_found->virus_name , list_head->virus_name);
                }
            }
            list_head = list_head->NEXT;
        }
        fseek(genome,-VIRUS_MAX_LEN,SEEK_CUR);
        /*there's no \n in the adn_assembly_output file so need to seek start then add the legnth of the best found virus*/
        fgets(adn_segment, virus_found->virus_len , genome);
        /*proceed to write down the virus and it's position*/
        v_position += virus_found->virus_len;

        fprintf(virus_scan_result,"virus: %s   ;    position: %ld\n",virus_found->virus.virus_name , v_position);
        /*now let's save it in our chain list*/
        virus_found = virus_found->NEXT;
    }
    virus_found = NULL;/* last one is null*/
    return virus_found_head;/* better return it aswell*/
}

int main(){
    virus_list* list_virus = init_virus_list();
    int VIRUS_MAX_LEN = make_virus_list(list_virus);

}
