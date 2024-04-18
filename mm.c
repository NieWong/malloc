/*
https://www.youtube.com/watch?v=8REdBgL_bXA&t=2s
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

#include <stdint.h>

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

#define ALIGNMENT 8

#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define BLK_HDR_SIZE ALIGN(sizeof(blockHdr))
#define SIZE_T_SIZE ALIGN(sizeof(size_t))

typedef struct header blockHdr;

struct header {
    size_t size;
    blockHdr *next_p;
    blockHdr *prior_p;
};

void *find_fit(size_t size);

int mm_init(void)
{
    blockHdr *p = mem_sbrk(BLK_HDR_SIZE);
    p->size = 1;
    p->next_p = p;
    p->prior_p = p;
    return 0;
}

void *mm_malloc(size_t size)
{
    int newsize = ALIGN(BLK_HDR_SIZE + size);
    blockHdr *bp = find_fit(newsize);
    if(bp == NULL){
        bp = mem_sbrk(newsize);
        if((long)bp == -1) 
            return NULL;
        else {
            bp->size = newsize | 1;
        }
    } else {
        bp->size = newsize |= 1;
        bp->prior_p->next_p = bp->next_p;
        bp->next_p->prior_p = bp->prior_p;
    }
    return (char *)bp + BLK_HDR_SIZE;
}

void *find_fit(size_t size){
    blockHdr *p;
    for(p = ((blockHdr *)mem_heap_lo())->next_p;
        p != mem_heap_lo() && p->size < size;
        p = p->next_p);

    if(p != mem_heap_lo())
        return p;
    else return NULL;
}

void mm_free(void *ptr)
{
}

void *mm_realloc(void *ptr, size_t size){
    return NULL; // Added missing semicolon
}
