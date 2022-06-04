/*Ben Elleman*/
#include <stdio.h>

#include "define.h"
#include "debug.h"

#include "motion.h"

#include "output.h"
#include "llfunc.h"

/* Function to compute the x, and y values of an alien based on deltaT, vX, and vY. */
void motion(void *ptr) {
	struct alienData *aD = (struct alienData*) ptr;
	aD->x = aD->x + aD->vX * ((struct simulation*) aD->sim)->dT;
	aD->y = aD->y + aD->vY * ((struct simulation*) aD->sim)->dT;
	if (aD->x >= XBOUND && aD->vX > 0.0 || aD->x <= -XBOUND && aD->vX < 0.0) {
		/*Imo the work done by edgcase and motion is all one job, and can all be done in one function, but
		 * just to be safe(and lame)*/
		/*Trust that another part of the sim will delete the ufos*/
		if (aD->type != UFO) edgeCase(aD);
		if (((struct simulation*)aD->sim)->outFile && aD->type != UFO) boundryOutput(*aD);
	}
}

/*Writes the bounce message to the screen*/
void boundryOutput(struct alienData aD) {
	/*outFile is known to not be null if this function is called*/
	FILE* outFile = ((struct simulation*)aD.sim)->outFile; 
	fprintf(outFile, 
		"\nAlien 0x%08X drops to (%.5lf, %.5lf), vX to %+.5lf at ET = %.5lf\n",
		aD.data, aD.x, aD.y, aD.vX, ((struct simulation*)aD.sim)->time);
}

/*Function to handle when x gets too close to the edge*/
void edgeCase(struct alienData* aD) {
	/*Reverse vX*/
	aD->vX = 0.0 - aD->vX;
	/*Lower y by defined amount*/ 
	aD->y = aD->y - YLOWER;
	/*Cap y if needed*/
	if (aD->y < 0) aD->y = 0;
}

