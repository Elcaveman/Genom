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
#define VIRUS_MAX 200

typedef struct _virus{
    char virus_name[30];
    int  virus_len;
    char virus_genome[VIRUS_MAX];
    struct _virus* NEXT;
}virus;

typedef struct _virus_list{
    virus* head;
}virus_list;

int make_virus_list();

virus_list* VIRUS_SCAN();
