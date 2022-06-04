/*Ben Elleman*/
#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"

#include "linkedlist.h"
#include "invaders.h"

#include "debug.h"
#include "define.h"
#include "llfunc.h"
#include "memory.h"

/*Function to check if passed alien has a y position at or below zero*/
int isAtZero(void *ptr, void *unused) {
	struct alienData *aD = (struct alienData*) ptr;
	FILE* outFile = ((struct simulation*)aD->sim)->outFile;
	int boolean = (aD->y <= 0.0);
	if (boolean && outFile) {
		fprintf(outFile, "\nAlien 0x%X touches down at x=%lf!\n", aD->data, aD->x);
	}
	/*No corresponding message for graphics mode required*/
	return boolean;
}
	
/*Checks if an alien is aligned with the bolt and outputs corresponding messages*/
int alienBolt(void *ptr, void *unused) {
	int boolean;
	struct alienData* aD = (struct alienData*) ptr;
	FILE* outFile = ((struct simulation*)aD->sim)->outFile;
	/*Is the x-pos of the alien, truncated to an int, the same as basePos, also truncated to an int*/
	boolean = ((int) (aD->x) == (int) (((struct simulation*)(aD->sim))->basePos));
	if (boolean) {
		if (outFile) fprintf(outFile, "Bolt hit aliens at (%lf, %lf), scores %d points!\n",
			aD->x, aD->y, aD->points);
		if (GRAPHICS) sa_status("Bolt hits an alien!");
		((struct simulation*) aD->sim)->score += aD->points;
	}
	return boolean;
}

/*The function that the linked list uses to compare (and sort) it's members*/
int comparison(void *d1, void *d2) {
	struct alienData *a = (struct alienData*) d1;
	struct alienData *b = (struct alienData*) d2;
	/*If the y values aren't equal, return that comparison, otherwise sort by the raw data*/
	return ((a->y != b->y) ? a->y > b->y :  a->data > b->data);
}

/*Function to draw an alien*/
void alienDraw(void *ptr) {
	struct alienData *aD = (struct alienData*) ptr;
	sa_alien(aD->type, aD->color, aD->x, aD->y);
}

/*Function to check if an alien should escape*/
int escape(void *ptr, void *unused) {
	/*It would be so nice if I could call this while iterating through motion*/
	int boolean;
	struct alienData *aD = (struct alienData*) ptr;
	FILE* outFile = ((struct simulation*)aD->sim)->outFile;
	boolean = ((aD->x > XBOUND || aD->x < -XBOUND) && aD->type == UFO);
	if (boolean) {
		if (outFile) fprintf(outFile, "Flying saucer worth %d points escapes at ET = %lf!\n", 
			aD->points, ((struct simulation*)aD->sim)->time);
		if (GRAPHICS) sa_status("Flying saucer escapes!\n)");
	}
	return boolean;
}

/*Prints the tabular message per each alien*/
void tabular(void *ptr) {
	struct alienData* aD = (struct alienData*) ptr;
	FILE* outFile = ((struct simulation*)aD->sim)->outFile;
	if (outFile) fprintf(outFile, "0x%08X %1d %1d %3d (%9.5lf,%9.5lf) (%9.5lf,%9.5lf)\n", 
		aD->data, aD->type, aD->color, aD->points, aD->x, aD->y, aD->vX, aD->vY);
}

/*Linked-list criteria function that always returns true*/
int deleteAll(void *unusedA, void *unusedB) {
	return 1;
}

