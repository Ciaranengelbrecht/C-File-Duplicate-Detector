#include  "duplicates.h"

int nfiles  = 0;
long long int total_file_size = 0;
bool initial_dir = true;
typedef struct  {
    long long int inode;
} INODES ;

int i = 0; 
long long int fsize;

void scan_directory (const char * dirname, bool flaga)
{ 
    
    struct dirent * dp;
    DIR * dirp; 
        INODES *ino; 
    // Open the initial directory specified by "dirname" and cheks it was opened 
    dirp = opendir(dirname);
    if (initial_dir) {
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    } initial_dir = false;}

    struct stat stat_info;
    while((dp = readdir(dirp)) != NULL){
        char            pathname[MAXPATHLEN];
        sprintf(pathname, "%s/%s", dirname, dp->d_name);
        bool stop = false;
        /* "Readdir" gets subsequent entries from "dirp". */
        if (! dp) { //There are no more entries in this directory
            break;}	


    //IF -a IS NOT REQUESTED
    if(flaga == false){
    if(dp->d_name[0]!= '.' && !(dp->d_type & DT_DIR) && dp->d_type != DT_UNKNOWN && dp->d_type != DT_LNK){
        
        //  DETERMINE ATTRIBUTES OF THIS DIRECTORY ENTRY
        if(stat(pathname, &stat_info) == 0) {
        ino = realloc(ino, (1+i)*sizeof(ino[0]));
        ino[i].inode = stat_info.st_ino; 
        i++;
        //  ADD FILE TO HASHTABLE
        char str[16];
        sprintf(str, "%lld", stat_info.st_size);
        uint32_t h   = (hash_string(str))%HASHTABLE_SIZE;    // CHOOSE LIST/BUCKET TO ADD TO
        if(list_find(hashtable[h], pathname)) {break;}
        for(int j=0; j<i-1; j++) 
        {if (stat_info.st_ino == ino[j].inode) stop = true;}
        if(stop == false) {
        hashtable[h] = list_add(hashtable[h], pathname, stat_info.st_size);
        CHECK_ALLOC(hashtable[h]);
        ++nfiles; total_file_size = total_file_size + stat_info.st_size;}
    }}}
    
    //IF -a IS REQUESTED
    else if(flaga == true && !(dp->d_type & DT_DIR) && dp->d_type != DT_UNKNOWN && dp->d_type != DT_LNK) {

        //  DETERMINE ATTRIBUTES OF THIS DIRECTORY ENTRY
        if(stat(pathname, &stat_info) == 0 && !S_ISLNK(stat_info.st_mode)) {
        ino = realloc(ino, (1+i)*sizeof(ino[0]));
        ino[i].inode = stat_info.st_ino; 
        i++;
        //  ADD FILE TO HASHTABLE
        char str[16];
        sprintf(str, "%lld", stat_info.st_size);
        uint32_t h   = (hash_string(str))%HASHTABLE_SIZE;    // CHOOSE LIST/BUCKET TO ADD TO
        if(list_find(hashtable[h], pathname)) {break;}
        for(int j=0; j<i-1; j++) 
        {if (stat_info.st_ino == ino[j].inode) stop = true;}
        if(stop == false) {
        hashtable[h] = list_add(hashtable[h], pathname, stat_info.st_size);
        CHECK_ALLOC(hashtable[h]);
        ++nfiles; total_file_size = total_file_size + stat_info.st_size;}
    }}
        
        if (dp->d_type & DT_DIR && dp->d_type != DT_UNKNOWN && dp->d_type != DT_LNK) {
            //Check that the directory is not "dirp" or dirp's parent. 
            if (strcmp (dp->d_name, "..") != 0 &&
                strcmp (dp->d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
                path_length = snprintf(path, PATH_MAX, "%s/%s", dirname, dp->d_name);
                
                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length is too long.\n");
                    exit (EXIT_FAILURE);
                }
                //RECURSIVELY CALL "scan_directory" WITH NEW PATH
                scan_directory (path, flaga);
            }
	} 
    }
    
    // AFTER ITTERATING THROUGH ALL DIRECTORIES CLOSE DIRECTORY
    if (closedir (dirp)) {
        fprintf (stderr, "Unable to close '%s': %s\n",
                 dirname, strerror (errno));
        exit (EXIT_FAILURE);
    }
}
