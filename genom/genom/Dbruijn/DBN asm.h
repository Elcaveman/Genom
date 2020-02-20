#ifndef RHURAC_SOMEFILE_H
#define RHURAC_SOMEFILE_H

// #include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MALLOC(t,n) (t*)malloc(n*sizeof(t))
#define REALLOC(block,t,n) (t*)realloc(block,n)
#define READ_NUMBERS 1880
#define SEQUENCE_LEN 100
#define FQ_FILE_PATH "C:/Users/HP/Desktop/Projex/GENOME/project/data/ads1_week4_reads.fq"
#define OUTPUT_PATH  "C:/Users/HP/Desktop/Projex/GENOME/project/data/result ADN.txt"
#define VIRUS_FILE_PATH "C:/Users/HP/Desktop/Projex/GENOME/project/data/virus db.txt"
#define VIRUS_SCAN_RESULT "C:/Users/HP/Desktop/Projex/GENOME/project/data/scan result.txt"

/*                  PART1 stuff                 */
struct chain_list_for_arcs;


typedef struct de_bruijn_graph_noeud{
    /*it's adresse is saved in the DBN-GRAPH structure*/
    int occurences;/* utilisé dans la recherche des erreurs */
    char* k_mer;
    struct chain_list_for_arcs* list_sortant_head;/*list des arcs "sortant" de (id_sommet)*/
}DBN_noeud;


typedef struct chain_list_for_arcs{
    DBN_noeud* Terminale;
    int poids_arc;
    struct chain_list_for_arcs* Next; 
}arc_list;

typedef struct chain_list_noeuds{
    DBN_noeud* sommet;
    struct chain_list_noeuds* NEXT;
    struct chain_list_noeuds* PREV; /*used only in last part for the backtrack*/
}noeud_list;

typedef struct de_bruijn_graph{
    int moyenne_occurences; /* ppour correction des erreurs */
    /* si un élément apparait moins que la moyenne ça veut dire qu'il est érronné*/
    DBN_noeud* graph_head;
    noeud_list* graph_universe;/*universe means l'ensembles des noeud(sommets) utilisé*/
}DBN_GRAPH;

DBN_noeud* rechercher_string_in_DBN_graph(DBN_GRAPH* graph,char* string);

void create_noeud(DBN_GRAPH* graph , char* k_mer , DBN_noeud* noeud);
void init_DBN_graph(DBN_GRAPH* graph);
void add_to_universe(DBN_GRAPH* graph ,DBN_noeud* nd);
void read_seq(char* adn_seq,FILE* input);
void append_arc(DBN_noeud* noued_debut , DBN_noeud* noeud);
void DBN_graph_builder(DBN_GRAPH* graph);

float calculer_moyenne_occurences(DBN_GRAPH* graph);
int is_brother(char* string1 , char* string2 , int nbr_of_changes);
void arc_sortant_list_union(DBN_noeud* noeud_frequent , DBN_noeud* noeud_nonfreq);
void arc_entrant_union(DBN_GRAPH* graph, DBN_noeud* noeud_frequent , DBN_noeud* noeud_nonfreq);
void repalce_noeud(DBN_GRAPH* graph, DBN_noeud* noeud_frequent , DBN_noeud* noeud_nonfreq);

void corriger_erreur_type_read(DBN_GRAPH* graph);

void read_chemin_eulerien(noeud_list* chemin_eulerien);
void chemin_eulerien_makeNread(DBN_GRAPH* graph);

/*part1: THE BOSS*/
void ADN_ASSEMBLY();

/*                  PART2 STUFF                     */
typedef struct _virus{
    char* virus_name;
    int   virus_len;
    char* virus_genome;
}virus;

typedef struct _virus_list{
    virus virus;
    struct _virus_list* NEXT;
}virus_list;

int make_virus_list(virus_list* list_head_org);
/*part2 : The BOSS*/
virus_list* VIRUS_SCAN();


#endif