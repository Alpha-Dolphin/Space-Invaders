/*Ben Elleman*/

#include <stdio.h>

#include "invaders.h"

#include "altmem.h"
#include "debug.h"
#include "define.h"

#include "memory.h"

/*Function to allocate space for an alien*/
struct alienData* alienAlloc(FILE* outFile) {
	struct alienData* ptr;
	static int aliens = 0;
	ptr = alternative_malloc(sizeof(struct alienData));
	if (ptr) {
		aliens++;
		if (outFile) fprintf(outFile, "alienAlloc: %d allocated\n", aliens);
	} else { 
		if (outFile) fprintf(outFile, "alienAlloc: ERROR: Memory allocation failed\n");
	}
	return ptr;
}

/*Function to free an alien*/
void alienFree(void *data) {
	struct alienData* ptr = data;
	static int cleared = 0;
	FILE* outFile = ((struct simulation*)ptr->sim)->outFile; 
	alternative_free(ptr);
	ptr = NULL;
	cleared++;
	if (outFile) fprintf(outFile,"alienFree: %d freed\n", cleared);
	/*if (GRAPHICS) sa_status("alienFree: Memory freed\n");*/
}

