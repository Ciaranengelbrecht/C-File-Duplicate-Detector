#include  "duplicates.h"

//PRINTS STATISTICS IF NO OPTIONS ARE SELECTED
void find_stats( char * dirname)
{    
    find_dupes(dirname);
    printf("%i\n%lli\n%i\n%lli\n", nfiles, total_file_size, n_unique_files, min_total_size);
}
//PRINTS DUPLICATES OF INDICATED FILE
void find_files(char *filename, char *dirname)        
{   char buf[PATH_MAX];
    char *realpathname = realpath(filename, buf);
    find_dupes(dirname);

    for(int i=0 ; i<nduplicates ; ++i) {
        if(strcmp(dups[i].hash, strSHA2(realpathname))==0 && strcmp(dups[i].pathname, filename) !=0) 
	    printf("%s\n", dups[i].pathname);}
}
//PRINTS DUPLICATES OF INDICATED HASH VALUE
void find_hash(char *hash, char *dirname)        
{  
    for(int i =0; i<HASHTABLE_SIZE;i++) 
    {
        if(hashtable[i] != NULL) 
    {
        while(hashtable[i] != NULL) 
        {
            if(strcmp(hash, strSHA2(hashtable[i]->pathname)) == 0)
	        printf("%s\n", hashtable[i]->pathname);nduplicates++;
	        hashtable[i]	= hashtable[i]->next;
        }
    }
    } 
}

