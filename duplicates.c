//  CITS2002 Project 2 2021
//  Name:             Ciaran Engelbrecht
//  Student number:   23169641 
#include  "duplicates.h"

#define	OPTLIST	 "aAf:h:lq"	
//USAGE REPORT
void usage(char *progname)
{
    fprintf(stderr,"Usage: %s [options] dirname\n", progname);
    fprintf(stderr, "where options are:\n");
    fprintf(stderr, " -a\t\tcheck all files, including hidden files such as those begininng with '.'\n");
    fprintf(stderr, " -A\t\treport if this program attempts advanced features\n");
    fprintf(stderr, " -l\t\tlist all duplicate files found\n");
    fprintf(stderr, " -q\t\tquietly test if any duplicates exist\n");
    fprintf(stderr, " -f filename\tsearch for duplicates of this file\n");
    fprintf(stderr, " -h hash\tsearch for duplicates of this hash\n");

}
HASHTABLE *hashtable;
int main(int argc, char *argv[])
{
    hashtable  = malloc(HASHTABLE_SIZE * sizeof(LIST *));
    char *program_name = (program_name = strrchr(argv[0],'/')) ? program_name+1 : argv[0];
    int	  opt;
    bool aflag = false;
    bool lflag = false;
    bool qflag = false;
    bool fflag = false;
    bool hflag = false;

//  PROCESS COMMAND-LINE OPTIONS 
    opterr	= 0;
    char *file_name;
    char *HashValue;
    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        switch (opt) {

            case 'a' : aflag = !aflag;
            break;

            case 'A' : exit(EXIT_SUCCESS); // HAVE ATTEMPTED FIRST & SECOND ADVANCED TASKS

            case 'f' : fflag = !fflag;
            file_name = optarg;
            break;

            case 'h' : hflag = !hflag;
            HashValue = optarg;
            break;

            case 'l' : lflag = !lflag;
            break;

            case 'q' : qflag = !qflag;
            break;

            default :usage(program_name); exit(EXIT_FAILURE);
            break;
        }
    }
    //ALLOWS FOR MULTIPLE DIRECTORIES
    for (; optind<argc;optind++){
        //SCAN EACH DIRECTORY
        scan_directory(argv[optind], aflag);
    }
    if(qflag) {
                    find_dupes(argv[optind]);
                    exit(nduplicates == 0 ? EXIT_SUCCESS : EXIT_FAILURE); 

    } 
    if(fflag) {  
                    find_files(file_name, argv[optind]);        
                    exit(nduplicates > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    }
    else if(hflag) {
                    find_hash(HashValue, argv[optind]);        
                    exit(nduplicates > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    }
    else if(lflag) {
                    list_dupes(argv[optind]);
                    exit(nduplicates > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
            }
    
    else {
                    find_stats(argv[optind]);
        }

    return 0;
}

    
    

