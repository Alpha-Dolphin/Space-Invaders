/*Ben Elleman*/
#include <stdio.h>

#include "typedef.h"
#include "invaders.h"
#include "linkedlist.h"

#include "debug.h"
#include "define.h"

#include "code.h"
#include "memory.h"
#include "llfunc.h"

/* I'd rather use magic numbers defined in comments*/
#define pointsBits 535822336
#define typeBits 28672
#define colorBits 112
#define pointsShift 4 + 3 + 5 + 3 + 5
#define typeShift 4 + 3 + 5
#define colorShift 4

/*uuu points~~~~~ uuuuu typ uuuuu col uuuu
* 000 000 000 000 00000 000 00000 000 0000 */

/*Function to read alien points from hexdata*/
int readPoints(int data, FILE* outFile) {		
	/*Bitwise & data and 4th - 12th bits, shift right 20 bits to get rid of unused data*/
	int pTC = (data & (pointsBits)) >> (pointsShift);
	if (DEBUG) fprintf(outFile,"readPoints: Data %X, result %d\n", data, pTC);
	return pTC;
}

/*Function to read alien type from hexdata*/
int readType(int data, FILE* outFile) {
	/*Bitwise & data and 18th - 20th bits, shift right 12 bits to get rid of unused data*/
	int pTC = (data & (typeBits)) >> (typeShift);
        if (DEBUG) fprintf(outFile,"readType: Data %X, result %d\n", data, pTC);
	return pTC;
}

/*Function to read alien color from hexdata*/
int readColor(int data, FILE* outFile) {
	/*Bitwise & data and 26th - 28th bits, shift right 3 bits to discard unused data*/
	int pTC = (data & (colorBits)) >> (colorShift);
	if (DEBUG) fprintf(outFile, "readColor: Data %X, result %d\n", data, pTC);
	return pTC;
}

/*Function to read all of the alien data and pass all neccessary data to given pointers*/
int readAlien(struct alienData *aD, FILE* inFile, FILE* outFile) {
	/*scanf value to be returned*/
	int scan;
	scan = fscanf(inFile, "%x %lf %lf %lf %lf\n", &(aD->data), &(aD->x), &(aD->y), &(aD->vX), &(aD->vY));
	aD->points = readPoints(aD->data, outFile);
	aD->type = readType(aD->data, outFile);
	aD->color = readColor(aD->data, outFile);
	if (DEBUG)fprintf(outFile,
		"readAlien: Data - %X points - %d type - %d color - %d x - %lf y - %lf vX - %lf vY - %lf\n",
		aD->data, aD->points, aD->type, aD->color, aD->x, aD->y, aD->vX, aD->vY);
	return scan;
}

/*Function to read and feed aliens into the linked-list via malloced space*/
int readLoop(void* simLoc, FILE* inFile, FILE* outFile) {
	struct alienData aD; int rL; struct alienData *alloced;
	/* Due to readAlien being in the while condition, the outFile for the last alien will print twice in debug.
	 * However, it will only get added once like it is supposed to.*/
	while ((rL = readAlien(&aD, inFile, outFile)) == 5) {
		aD.sim = simLoc;
		alloced = alienAlloc(outFile);
		if (alloced) {
			*alloced = aD;
			/*Alien will automatically be freed if it can't insert*/
			if(!insert(&(((struct simulation*) simLoc)->list), alloced, comparison, outFile))
				alienFree(alloced);
			if (DEBUG && outFile) fprintf(outFile,"Added alien 0x%X to list\n", aD.data);
		}
	}
	if (outFile) fprintf(outFile,"Read loop exited, scanf returned %d\n", rL);
	return 1;
}

