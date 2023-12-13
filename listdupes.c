#include  "duplicates.h"

//STRUCT FOR POTENTIAL DUPLICATES
typedef struct  {
    char        *pathname;
    char		*hash;
    long long int filesize;
} POTENTIAL ;

POTENTIAL *pot_dups;
struct DUP *dups = NULL;

//SORTING FUNCTION FOR CONFIRMED DUPLICATES
int compare_hash(const void *v1, const void *v2)
{
    struct DUP *p1 = (struct DUP *)v1;
    struct DUP *p2 = (struct DUP *)v2;
    return strcmp(p1->hash,p2->hash);
} 

int z =0;
int k = 0;
int ndupes =0;
int n_unique_files = 0;
long long int min_total_size = 0;
int nduplicates=0; 

void list_dupes(char *dirname)
{   //ADD POTENTIAL DUPLICATES INTO ARRAY
    min_total_size = total_file_size;
    for(int i =0; i<HASHTABLE_SIZE;i++) {
    if(hashtable[i] != NULL && hashtable[i]->next != NULL) {
        while(hashtable[i] != NULL) {
        pot_dups = realloc(pot_dups, (i+1+z)*sizeof(pot_dups[0]));
        pot_dups[z].filesize = hashtable[i]->filesize;    
        pot_dups[z].hash = strSHA2(hashtable[i]->pathname);    
        pot_dups[z].pathname = strdup(hashtable[i]->pathname);
        z++;
	    hashtable[i] = hashtable[i]->next;
        }
	
    }} 
    //COMPARE LIST OF POTENTIAL DUPLICATES TO CONFIRM ACTUAL DUPLICATES
for(int i=0; i<z; i++)
    {
        for(int j=z-1; j>-1; j--)
        {
            //If duplicate found then increment count by 1 
            if(strcmp(pot_dups[i].hash, pot_dups[j].hash)==0 && i !=j)
            {dups = realloc(dups, (i+1)*sizeof(dups[0]));
             dups[k].filesize = pot_dups[i].filesize;
             dups[k].hash = pot_dups[i].hash;
             dups[k].pathname = pot_dups[i].pathname;
             k++; nduplicates++;
             break;
            }
        }
    }

    //SORT DUPLICATES TO BE IN ORDER & PRINT OUT SEPARATED BT TAB
    qsort((void *)dups, k, sizeof(struct DUP), compare_hash);
    for(int j= 1; j < k; j++) {    
    if(strcmp(dups[j].hash, dups[j-1].hash)==0){
        printf("%s    ", dups[j-1].pathname); //printf("-> "); 
        ndupes++; min_total_size = min_total_size - dups[j-1].filesize;
    }else{
        printf("%s", dups[j-1].pathname); printf("\n");
    }}  printf("%s\n", dups[k-1].pathname); 
    n_unique_files = nfiles-ndupes;
}

//FIND DUPLICATES WITHOUT PRINTING
void find_dupes(char *dirname)
{
    min_total_size = total_file_size;
    for(int i =0; i<HASHTABLE_SIZE;i++) {
    if(hashtable[i] != NULL && hashtable[i]->next != NULL) {
        while(hashtable[i] != NULL) {
        pot_dups = realloc(pot_dups, (i+1+z)*sizeof(pot_dups[0]));
        pot_dups[z].filesize = hashtable[i]->filesize; 
        pot_dups[z].hash = strSHA2(hashtable[i]->pathname);
        pot_dups[z].pathname = strdup(hashtable[i]->pathname);
        z++;
	    hashtable[i]	= hashtable[i]->next;
        } 
    }} 

    
for(int i=0; i<z; i++)
    {
        for(int j=z-1; j>-1; j--)
        {
            //If duplicate found then increment count by 1 
            if(strcmp(pot_dups[i].hash, pot_dups[j].hash)==0 && i !=j)
            {dups = realloc(dups, (i+1)*sizeof(dups[0]));
             dups[k].filesize = pot_dups[i].filesize;
             dups[k].hash = pot_dups[i].hash;
             dups[k].pathname = pot_dups[i].pathname;
             k++; nduplicates++;
             break;
            }
        }
    }

    qsort((void *)dups, k, sizeof(struct DUP), compare_hash);
    for(int j= 1; j < k; j++) {    
    if(strcmp(dups[j].hash, dups[j-1].hash)==0){
    ndupes++; min_total_size = min_total_size - dups[j-1].filesize;
    }}  n_unique_files = nfiles-ndupes;
}


