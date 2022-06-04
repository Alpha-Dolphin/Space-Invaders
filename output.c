/*Ben Elleman*/
#include <stdio.h>

#include "invaders.h"

#include "define.h"
#include "debug.h"

#include "output.h"

#include "typedef.h"
#include "linkedlist.h"
#include "motion.h"
#include "code.h"
#include "memory.h"
#include "llfunc.h"
#include "jumpTable.h"

#define millisecConv 1000.0
#define microsecConv 1000000

/*Order: Shared functions, graphical functions, text functions*/

/*Determines if a new second has occured*/
int newSecond(const struct simulation *sim){
	/*Is time, truncated to an int, the same as it was one frame ago aka dT ago*/
	int cur, prev;
	cur = (int) (sim->time);
	prev = (int) (sim->time - sim->dT);
	if (DEBUG && sim->outFile) fprintf(sim->outFile,"newSecond: Cur = %d, prev = %d, ET = %lf: returning %d\n",
		cur, prev, sim->dT, (cur != prev));
	return cur != prev;
}

/*Handles all of the graphics loop functions whose behavior remains constant*/
void constGraphics(struct simulation *sim) {
	sa_time((int) (millisecConv * sim->time));
	sa_score(sim->score);
	sa_base(sim->basePos);
	sa_refresh();
	microsleep((unsigned int) (sim->dT * microsecConv));
}

/*Hold the sim for ENDSIMDELAY seconds*/ 
void simDelay(struct simulation* sim) {
	double delay = 0.0;
	while (delay <= ENDSIMDELAY) {
		sa_clear();
		iterate(sim->list, alienDraw);
		userControl(sim);
		constGraphics(sim);
		delay += sim->dT;
	}
}

/*Final text output at the end of the sim*/
void finalOutput(const struct simulation *sim) {
        if (sim->outFile) {
		sim->list ? fprintf(sim->outFile,"\n\nDefeat! Alien lands") :
			fprintf(sim->outFile,"\n\nVictory! No attackers remain");
		fprintf(sim->outFile," at ET = %lf\nTotal score is %d points\n", sim->time, sim->score);	
	}
}

/*Do all tabular related output*/
void tabOutput(const struct simulation *sim) {
	if (sim->outFile) 
		fprintf(sim->outFile,"\nCode       T C Pts ( __X_____, __Y_____) ( __VX____, __VY____) ET= %.5lf\n",
		sim->time);
	iterate(sim->list,tabular);
	if (sim->outFile) fprintf(sim->outFile,"\n");
}
