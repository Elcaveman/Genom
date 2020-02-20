#include "DBN asm.h"

/*                          I- Sequençage d'ADN using the de Bruijn graph method                        */
int k =37;/* the k-mer for de bruijn graphs (need to make it as an input)*/

/*définitions des structures dans  file 1 .h*/

DBN_noeud* rechercher_string_in_DBN_graph(DBN_GRAPH* graph,char* string){
    /* cette fonction recherche un str dans le graph et retourne le sommet
    contenant ce str (il n'a pas de répitition de str)*/
    noeud_list* head = graph->graph_universe;
    int flag=1;
    while (head!=NULL && flag!=0){
        head= head->NEXT;
        flag = strcmp(head->sommet->k_mer,string);/*if the strings are != then flag!=0*/
        /* yu can't printf flag for sm reason*/
    }
    return head->sommet; /*NUll if doesn't exist else &sommet */
}

DBN_noeud* create_noeud(DBN_GRAPH* graph , char* k_mer){
    DBN_noeud* nd = rechercher_string_in_DBN_graph(graph , k_mer);
    if (nd==NULL){
        nd->occurences = 1;
        strcpy(nd->k_mer,k_mer);
        nd->list_sortant_head = NULL;
        graph->graph_universe->sommet = nd;
        graph->graph_universe->NEXT = NULL;
    }
    else{ 
        nd->occurences +=1; /*the k-mer occures another time*/
    }
    return nd;
    /*return the adress of the already existant or new nod*/
    
}

void init_DBN_graph(DBN_GRAPH* graph){
    graph->graph_head = MALLOC(DBN_noeud,1);
    graph->graph_universe = MALLOC(noeud_list,1);
}

void append_arc(arc_list* arc_lis_head , DBN_noeud* noeud){
    arc_list* cop = arc_lis_head;
    while (cop!=NULL){
        if (cop->Terminale == noeud){
            cop->poids_arc +=1 ;/*arc already exists so we append nothing*/
            return;
        }
        cop = cop->Next;
    }
    cop = MALLOC(arc_list,1);
    cop->poids_arc = 1;
    cop->Terminale = noeud;
    cop->Next = NULL;
}
/*              PART1: BUILDING THE GRAPH                       */
void DBN_graph_builder(DBN_GRAPH* graph){
    /*This cutie is used to build the DBN graph*/
    FILE *input  = fopen(FQ_FILE_PATH, "r"); // File with sequencer result (.FQ)
    char adn_seq[SEQUENCE_LEN];
    char _[SEQUENCE_LEN];/*smth we won't use*/
    int start;
    init_DBN_graph(graph);
    DBN_noeud* head = graph->graph_head;

    for (int i=0 ; i<READ_NUMBERS ; i++){
        fscanf(input, "%s\n%s\n%s\n%s", &_, &adn_seq,&_,&_);
        /*gets (k-1)-mers directly*/
        start = 0;
        while (start+(k-1)<SEQUENCE_LEN){/*k-mers loop*/
            /*get the k-1 mers*/
            char* left_kmer = MALLOC(char,k-1);
            char* right_kmer = MALLOC(char,k-1);
            for (int j = 0 ; j<(k-1); j++){
                *(left_kmer+j) = adn_seq[start+j];
                *(right_kmer+j) = adn_seq[start+j+1];
            }
            /*we made the left/right K-mers let's make nods for em and link em*/
            /*STEP1:  make nod if it's a new element else get it's location*/
            DBN_noeud* elt1 = create_noeud(graph , left_kmer);
            DBN_noeud* elt2 = create_noeud(graph , right_kmer);
            if (i==0 && start==0){
                /*in the first iteration we need to save the graphs head (le premier element)*/
                graph->graph_head = elt1;
            }
            /*STEP2:  create arc between left and right k-mers*/
            append_arc(elt1->list_sortant_head,elt2);
            start ++;
        }
    }
    fclose(input);
}

/*              PART2: HUNTING FOR ERRORS                       */
/*         TYPE1: Erreurs sur les reads                         */
float calculer_moyenne_occurences(DBN_GRAPH* graph){
    /*calcule la moyenne des occurences de tout les sommets du DBN graph (après création) */
    noeud_list* list_sommets = graph->graph_universe;
    int ordre =0; /* nombre de sommets enregistré */
    int moy = 0;
    while (list_sommets!=NULL){
        ordre +=1;
        moy += (float)list_sommets->sommet->occurences;
    }
    if (ordre ==0) {printf("graph vide dude");return 0;}
    else{
        moy = moy/(float)ordre;
        graph->moyenne_occurences = moy;/* can save ordre if i want to */
        return moy;
    }
}
// free_sommet(DBN_noeud* noeud){
//     free(noeud->k_mer);
//     free(noeud->list_sortant_head);
//     free(noeud);
// }
// free_arc(arc_list* arc_element){
//         /*to be tested */
//         free_sommet(arc_element->Terminale);
//         free(arc_element->poids_arc);
//         free(arc_element);
//}

/* on suppose que le porcentage d'erreur est de 0.1% 1erreur/10@read 
   donc on peut traiter 99,7% des erreurs en supposant que sur chaque read éxiste au max *une erreur*/

int is_brother(char* string1 , char* string2 , int nbr_of_changes){
    /* return 0 if not brother // 1 else --> CAT,CAA,TAT,CTT are bros of nbr_of_change =1 */
    int counter=0;
    /* on suppose que strlen(string1)==strlen(string2) */
    int len = strlen(string1);
    for (int i=0 ; i<len ; i++ ){
        if  ( *(string1+i)!=*(string2+i)){
            counter+=1;
        }
        if (counter>nbr_of_changes) return 0; // meilleur complexité
    }
    if (counter == nbr_of_changes) return 1;
    return 0;
}
/* on utilisera nbr_of_changes ==1 partout dans le programme */

void arc_sortant_list_union(DBN_noeud* noeud_frequent , DBN_noeud* noeud_nonfreq){
    arc_list* nonfreq_head = noeud_nonfreq->list_sortant_head;
    int initial_len_listfreq = 0;
    int flag = 0 ;
    while (nonfreq_head!=NULL){

        arc_list* freq_head = noeud_frequent->list_sortant_head;/* reset head */
        if (flag==0){
            while (freq_head!=NULL){
                initial_len_listfreq+=1;
                if (freq_head->Terminale == nonfreq_head->Terminale){
                    freq_head->poids_arc += nonfreq_head->poids_arc;
                }
                freq_head = freq_head->Next;
            }
            flag=1;
        }
        if (flag==1){
            for (int i=0 ; i<initial_len_listfreq ; i++){
                /* pour optimiser le temps car on aura pas besoin d'iterer sur les éléments reçament ajouté */
                if (freq_head->Terminale == nonfreq_head->Terminale){
                freq_head->poids_arc += nonfreq_head->poids_arc;
                break;
                }
                freq_head = freq_head->Next;
            }
        }
        freq_head->Next = nonfreq_head;/* on ajoute cet elment non existant  à la liste des neuds sortant du nod_frequent */

        nonfreq_head = nonfreq_head->Next;
        if (nonfreq_head ==NULL) freq_head->Next = NULL; /* for the last one */
    }
    noeud_nonfreq->list_sortant_head = NULL; /* car on va le suprimer de la mémoire avec free alors vos mieux le disjoindre
    avec ses ex_pointeurs! */
}

void arc_entrant_union(DBN_GRAPH* graph, DBN_noeud* noeud_frequent , DBN_noeud* noeud_nonfreq){
    
    noeud_list* head = graph->graph_universe;
    int save_noeud_frequent_poids;
    int save_noeud_nonfreq_poids ;
    int flag ;

    while (head!=NULL){
        arc_list* arc_head = head->sommet->list_sortant_head;

        save_noeud_nonfreq_poids = 0;
        save_noeud_frequent_poids =0;
        flag = 0;

        arc_list* position_freq = MALLOC(arc_list , 1);
        arc_list* position_nonfreq = MALLOC(arc_list , 1);

        arc_list* save_precedent_nonfreq = MALLOC(arc_list , 1);

        while (arc_head != NULL){
            if (arc_head->Terminale == noeud_frequent){
                save_noeud_frequent_poids = arc_head->poids_arc;
                position_freq = arc_head;/* on en aura besoin par après */
            }
            if (arc_head->Terminale == noeud_nonfreq && save_noeud_frequent_poids!=0){
                /* ce cas veut dire que freq et nonfreq sont des noeuds que head->sommet entre dedans */
                save_precedent_nonfreq->Next = arc_head->Next;/* skips the element arc_head cuz it'll be deleted */
                position_freq->poids_arc += arc_head->poids_arc;
                free(arc_head);/* to be tested */
                break;
                /* mn hna kat khrj naadi (yu don't save pos_nonfreq) */
            }
            if(arc_head->Terminale == noeud_nonfreq && save_noeud_frequent_poids==0){
                /* save it in case we pass it the we find the frequent nod then see line 220 */
                position_nonfreq = arc_head;
                flag=1; /* plus besoin de faire bouger save_precedent_nonfreq*/
            }

            if (flag==0) save_precedent_nonfreq = arc_head;

            arc_head = arc_head->Next;
        }

        if (save_noeud_frequent_poids==0 && position_nonfreq!= NULL){
            position_nonfreq->Terminale = noeud_frequent;/* le poids reste le meme */
        }
        if (save_noeud_frequent_poids!=0 && position_nonfreq!= NULL){/* line 220 */
            save_precedent_nonfreq->Next = position_nonfreq->Next;/* skips the element save_nonfreq cuz it'll be deleted */
            position_freq->poids_arc += position_nonfreq->poids_arc;
            free(position_nonfreq);
        }
        head = head->NEXT;
    }
}

void repalce_noeud(DBN_GRAPH* graph, DBN_noeud* noeud_frequent , DBN_noeud* noeud_nonfreq){
    /* avant de suprimer noeud_nonfreq */
    noeud_frequent->occurences += noeud_nonfreq->occurences;
    arc_sortant_list_union(noeud_frequent , noeud_nonfreq);
    arc_entrant_union(graph , noeud_frequent , noeud_nonfreq);
    if (noeud_nonfreq == graph->graph_head){
        graph->graph_head = noeud_frequent;
    }
    noeud_list* univers = graph->graph_universe;
    noeud_list* precedent;
    while(univers->sommet != noeud_nonfreq){/* existe forcément dans notre cadre d'étude */
        univers = univers->NEXT;
        precedent = univers;
    }
    precedent->NEXT = univers->NEXT;/* ainsi on a skipper noeud_nonfreq dans l'univers de graph (supprimer) */
    free(univers->sommet);
    
}

void corriger_erreur_type_read(DBN_GRAPH* graph){
    /* la séquence qu'on remplace n'est pas forcement correcte !*/
    float tresh = calculer_moyenne_occurences(graph);
    noeud_list* list_sommets_idx1 = graph->graph_universe;
    noeud_list* list_sommets_idx2 = graph->graph_universe;
    while (list_sommets_idx1!=NULL){
        DBN_noeud* sommet_unfreq = list_sommets_idx1->sommet;
        if (sommet_unfreq->occurences < tresh){
            /* c'est probablemnt une erreur on cherche son premier bro */
            while (list_sommets_idx2!=NULL){
                DBN_noeud* sommet_frere = list_sommets_idx2->sommet;
                if (sommet_frere->occurences > tresh && is_brother(sommet_frere->k_mer , sommet_unfreq->k_mer,1)){
                    repalce_noeud(graph,sommet_frere , sommet_unfreq);
                    break;
                }
                list_sommets_idx2 = list_sommets_idx2->NEXT;
            }
        }
    }
}
/*          TYPE2: error topographie du graph (non implementé)          */

/*              PART3: EULERIEN WALK AND GETTING THE GENOME!!   */
void read_chemin_eulerien(noeud_list* chemin_eulerien){
    /*doing concatenation*/
    FILE* output = fopen(OUTPUT_PATH , "w");
    char* full_adn = MALLOC(char,1);
    int flag =1;
    while(chemin_eulerien!=NULL){
        if (flag==1){
            strcpy(full_adn,chemin_eulerien->sommet->k_mer);
            flag =0;
        }
        else{
            int last = strlen(chemin_eulerien->sommet->k_mer)-1;/*last element position*/
            char* convert_char_string = MALLOC(char,1);
            *convert_char_string = chemin_eulerien->sommet->k_mer[last];
            strcat(full_adn , convert_char_string);
            /*adds last element to the existing full_adn*/
            chemin_eulerien = chemin_eulerien->NEXT;
        }
    }
    fprintf(output , "%s",full_adn);
}

void chemin_eulerien_makeNread(DBN_GRAPH* graph){
    
    noeud_list* chemin = MALLOC(noeud_list , 1);
    DBN_noeud* graph_head = graph->graph_head;
    noeud_list* universe = graph->graph_universe;
    noeud_list* backtrack = MALLOC(noeud_list , 1);

    backtrack->sommet = graph_head;
    backtrack->PREV = NULL;
    backtrack = backtrack->NEXT;

    chemin->NEXT = NULL;

    int loop_cond =1;
    while (loop_cond)
    {
        int stuk = 0;
        arc_list* arc_lis = graph_head->list_sortant_head;
        while(arc_lis!=NULL){
            if (arc_lis->poids_arc!=0) break;
            else arc_lis = arc_lis->Next;
        }
        if (arc_lis == NULL) stuk =1;
        if (stuk == 0){
            /*goes ahead*/
            backtrack->sommet = arc_lis->Terminale;
            backtrack->PREV = backtrack;
            backtrack = backtrack->NEXT;

            arc_lis->poids_arc -=1;    
        }
        else{
            /* back-track*/
            if (backtrack->PREV == NULL)loop_cond==0;
            else{
                backtrack = backtrack->PREV;/*the position backtrack is pointing to now is empty so need to go back first*/
                chemin->sommet = backtrack->sommet;
                noeud_list* _ = chemin;
                chemin = chemin->PREV;/*okay so we was : [(?,?)<-(?,?)*->NULL]--> [(?,?)*<-(?,somet1)->NULL]*/
                chemin->NEXT = _ ;     /*now we are : [(?,?)*<->(?,somet1)<->NULL] we can go both ways*/
                backtrack = backtrack->PREV;/* goes back to see if any other way exist*/
            }
        }   
    }
    read_chemin_eulerien(chemin);
}

/* PART1 BOSS*/
void ADN_ASSEMBLY(){
    DBN_GRAPH graph;
    DBN_graph_builder(&graph);
    corriger_erreur_type_read(&graph);
    chemin_eulerien_makeNread(&graph);
}
/*                   II- Recherche de fausse souche dans le GENOME généré en utilisant des arbres   */

/* RECHERCHE NORMALE*/
/* sturcts used in .h file!!    */
int make_virus_list(virus_list* list_head_org){
    int max_len=0;
    FILE* virus_db = fopen(VIRUS_FILE_PATH,"r");
    virus_list* list_head = list_head_org;
    while (fscanf(virus_db,"%s_%d : %s\n",list_head->virus.virus_name,list_head->virus.virus_len,list_head->virus.virus_genome)!=EOF){
        if (max_len < list_head->virus.virus_len) max_len = list_head->virus.virus_len;
        list_head = list_head->NEXT;
    }
    list_head = NULL;/*last one is null*/
    return max_len; /*utile*/
}

virus_list* VIRUS_SCAN(){
    virus_list* list_head_org;
    int VIRUS_MAX_LEN = make_virus_list(list_head_org);

    virus_list* virus_found = MALLOC(virus_list,1);
    virus_found->virus.virus_len =0;
    virus_list* virus_found_head = virus_found;

    FILE* virus_scan_result = fopen(VIRUS_SCAN_RESULT,"w");
    FILE* genome = fopen(OUTPUT_PATH,"r");

    long v_position = 0;/*the start position of the virus obv*/
    char* adn_segment = MALLOC(char,200);

    while(fgets(adn_segment,VIRUS_MAX_LEN,genome)!=NULL){ 
        /* fgets reads line till it finds a \n or a set number of bytes*/
        /* returns NULL if the reading was unsuccessefull*/
        virus_list* list_head = list_head_org;
        
        while (list_head!=NULL){
            int len = list_head->virus.virus_len;
            if (strncmp(adn_segment , list_head->virus.virus_genome , len) ==0 ){
                if (virus_found->virus.virus_len < len ){
                    virus_found->virus.virus_genome = list_head->virus.virus_genome;
                    virus_found->virus.virus_len = list_head->virus.virus_len;
                    virus_found->virus.virus_name = list_head->virus.virus_name;
                }
            }
            list_head = list_head->NEXT;
        }
        fseek(genome,-VIRUS_MAX_LEN,SEEK_CUR);
        /*there's no \n in the adn_assembly_output file so need to seek start then add the legnth of the best found virus*/
        fgets(adn_segment, virus_found->virus.virus_len , genome);
        /*proceed to write down the virus and it's position*/
        v_position += virus_found->virus.virus_len;

        fprintf(virus_scan_result,"virus: %s   ;    position: %ld\n",virus_found->virus.virus_name , v_position);
        /*now let's save it in our chain list*/
        virus_found = virus_found->NEXT;
    }
    virus_found = NULL;/* last one is null*/
    return virus_found_head;/* better return it aswell*/
}

int main(){
    ADN_ASSEMBLY();
}