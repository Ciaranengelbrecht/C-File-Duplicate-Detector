#include "duplicates.h"

LIST *list_new(void)
{
    return NULL;
}

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *wanted)
{
    while(list != NULL) {
	if(strcmp(list->pathname, wanted) == 0) {
	    return true;
	}
	list	= list->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
LIST *list_new_item(char *newstring, long long int newsize)
{
    LIST *new       = malloc( sizeof(LIST) );
    CHECK_ALLOC(new);
    new->pathname     =  strdup(newstring);
    new->filesize     =  newsize;
    CHECK_ALLOC(new->pathname);
    new->next       =  NULL;
    return new;
}


//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, char *newstring, long long int newsize)
{
    if(list_find(list, newstring)) { // only add each item once
        return list;
    } 
    else
    {                                  // add new item to head of list
        LIST *new   = list_new_item(newstring, newsize);
        new->next   = list;
        return new;
        
    }
}


//  --------------------------------------------------------------------
#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

uint32_t hash_string(char *string)
{ //FNV32 http://ctips.pbworks.com/w/page/7277591/FNV%20Hash
    uint32_t hash = FNV_OFFSET_32, i;
    for(i = 0; i < strlen(string); i++)
    {   
        hash = hash ^ (string[i]); // xor next byte into the bottom of the hash
        hash = (hash * FNV_PRIME_32); // Multiply by prime number found to work well
        
    }
    return hash;
    
}

