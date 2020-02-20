#include "file 1 .h"

int k =37;/* the k-mer for de bruijn graphs (need to make it as an input)*/

/*définitions des structures dans  file 1 .h*/

DBN_noeud* rechercher_string_in_DBN_graph(DBN_GRAPH* graph,char* string){
    /* cette fonction recherche un str dans le graph et retourne le sommet
    contenant ce str (il n'a pas de répitition de str)*/
    noeud_list* head = graph->graph_universe;
    printf("rech start");
    while (head!=NULL){
        /*if the strings are != then flag!=0*/
        if (strcmp(head->sommet->k_mer,string) ==0) {
            return head->sommet;
            break;
        }
        head= head->NEXT;
    }
    return NULL;/*NUll if doesn't exist else &sommet */
}
void add_to_universe(DBN_GRAPH* graph ,DBN_noeud* nd){
    
    if (graph->graph_universe==NULL){
        noeud_list head;
        head.sommet = nd;
        head.PREV = NULL;
        head.NEXT = NULL;
        graph->graph_universe = &head;    
    }
    else{
        noeud_list* head;
        while (head->NEXT!=NULL){
            head = head->NEXT;
        }
        head->NEXT->sommet = nd;
        head->NEXT->PREV = head;
        head->NEXT->NEXT = NULL;
    }
}

void create_noeud(DBN_GRAPH* graph , char k_mer[] , DBN_noeud* noeud){
    DBN_noeud* nd = rechercher_string_in_DBN_graph(graph , k_mer);
    if (nd==NULL){
        noeud->occurences = 1;
        strcpy(noeud->k_mer,k_mer);
        noeud->list_sortant_head = NULL;
        add_to_universe(graph , noeud);
    }
    else{ 
        noeud = nd;
        noeud->occurences +=1; /*the k-mer occures another time*/
    }
    /*return the adress of the already existant or new nod*/
    
}

void init_DBN_graph(DBN_GRAPH* graph){
    graph->graph_head = MALLOC(DBN_noeud,1);
    graph->graph_universe = NULL;
}

void append_arc(DBN_noeud* noued_debut , DBN_noeud* noeud){
    arc_list* cop = noued_debut->list_sortant_head;
    arc_list helox;
    printf("\nhellox :%p\n",&helox);
    printf("cop: %p\n",cop);
    /*cop is actually like an alias for list_sortant*/
    /*but if you change cop it self list_sortant won't be updated*/
    helox.poids_arc = 1;
    /*makes a copy of noeud*/
    DBN_noeud nd ;
    strcpy(nd.k_mer ,noeud->k_mer);
    nd.occurences = noeud->occurences;
    nd.list_sortant_head = noeud->list_sortant_head;

    helox.Terminale = &nd;
    
    helox.Next = NULL;
    
    if (cop == NULL){
        noued_debut->list_sortant_head = &helox;
        printf("%p\n",&helox);
    }
    else{
        while (cop->Next!=NULL){
            if (cop->Terminale == noeud){
                cop->poids_arc +=1 ;/*arc already exists so we append nothing*/
                return;
            }
            cop = cop->Next;
        }
        cop->Next = &helox;
        printf("cop next : %p\n ",cop->Next);
    }
    
}
/*              PART1: BUILDING THE GRAPH                       */
void read_seq(char* adn_seq,FILE* input){
    char garbage[100];char ok[100];
    fscanf(input , "%s",ok);
    fscanf(input , "%s",adn_seq);
    fscanf(input , "%s",garbage);
    fscanf(input , "%s",garbage);
}
void DBN_graph_builder(DBN_GRAPH* graph){
    /*This cutie is used to build the DBN graph*/
    FILE *input  = fopen(FQ_FILE_PATH, "r"); // File with sequencer result (.FQ)
    char adn_seq[100];
    int start;
    init_DBN_graph(graph);
    DBN_noeud* head = graph->graph_head;

    for (int i=0 ; i<READ_NUMBERS ; i++){
        read_seq(adn_seq,input);
        /*gets (k-1)-mers directly*/
        printf("%s\n" , adn_seq);
        /*I don't know why but this printf makes the program work*/
        start = 0;
        while (start+(k-1)<SEQUENCE_LEN){/*k-mers loop*/
            /*get the k-1 mers*/
            char left_kmer[k];
            char right_kmer[k];
            for (int j = 0 ; j<(k-1); j++){
                right_kmer[j] = adn_seq[start+j+1];
                left_kmer[j]  = adn_seq[start+j];
            }
            printf("%d",strlen(right_kmer));
            printf("left: %s \n right: %s\n" ,left_kmer , right_kmer);
            /*we made the left/right K-mers let's make nods for em and link em*/
            /*STEP1:  make nod if it's a new element else get it's location*/

            DBN_noeud* elt1 = MALLOC(DBN_noeud , 1); 
            
            create_noeud(graph , right_kmer, elt1);
            DBN_noeud* elt2 = MALLOC(DBN_noeud , 1);
        
            create_noeud(graph , left_kmer , elt2);

            if (i==0 && start==0){
                /*in the first iteration we need to save the graphs head (le premier element)*/
                graph->graph_head = elt1;
            }            
            /*STEP2:  create arc between left and right k-mers*/
            append_arc(elt1,elt2);
            start ++;
        }
    }
    fclose(input);
}

int main(){
    DBN_GRAPH graph;
    DBN_graph_builder(&graph);
    system("pause");
}