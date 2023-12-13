#define _GNU_SOURCE
#include  <stdio.h>
#include  <stdbool.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <sys/param.h>
#include  <string.h>
#include  <getopt.h>
#include  <errno.h>

#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

#if     defined(__linux__)
extern         char *strdup(const char *s);
#endif

#define	HASHTABLE_SIZE		300007//999983//98387/

// DECLARATIONS OF FUNCTIONS
extern void list_dupes(char *dirname);
extern void find_hash(char *hash, char *dirname);
extern void find_files(char *filename, char *dirname);  
extern char *strSHA2(char *filename);
extern void scan_directory (const char * dirname, bool flaga);
extern void find_stats( char * dirname);
extern void find_dupes(char *dirname);        

//  GLOBAL COUNTERS
extern int nfiles;//the total number of files found,
extern long long int total_file_size;//the total size (in bytes) of all files found,
extern int n_unique_files;//the total number of unique files (i.e. any duplicate is only counted once), and
extern long long int min_total_size;//the possible minimum total size of all files found (i.e. the sizes of duplicated files are only counted once).

extern    int nduplicates;
extern    int ndupes;
extern	  bool *aflag;
extern	  DIR * dirp;
extern    struct dirent * dp;

//HASHTABLE 
struct _list {
    char        *pathname;
	long long int			filesize;
    struct _list   *next;
} typedef LIST;
	
typedef	LIST * HASHTABLE;
extern HASHTABLE *hashtable;

extern	LIST	*list_new(void);
extern	LIST	*list_add(LIST *list, char *newstring, long long int newsize);
extern	bool	 list_find (LIST *list, char *wanted);
extern uint32_t hash_string(char *string);

struct DUP {
    char        *pathname;
    char		*hash;
    long long int	filesize;
};
extern struct DUP *dups;

