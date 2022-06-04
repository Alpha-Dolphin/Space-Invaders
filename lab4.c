/*Ben Elleman*/
#include <stdio.h> 

#include "typedef.h"
#include "linkedlist.h"
#include "invaders.h"

#include "define.h"
#include "debug.h"

#include "lab4.h"

#include "code.h"
#include "output.h"
#include "motion.h"
#include "llfunc.h"
#include "memory.h"
#include "files.h"
#include "jumpTable.h"

/*Tracks beginning and end times, calls textGraphics, and prints total running time*/
int main(int argc, char *argv[]) {
	double beginning;
	beginning = now();
	textGraphics(argc, argv);
	printf("Total program run time is %.9lf seconds\n", now() - beginning);
	return EXIT_SUCCESS;
}

/*Initializes the sim struct and calls the appropiate master channels*/
void textGraphics(int argc, char *argv[]) {
	struct simulation sim = {0.0, NULL, 0.0, 0, deltaT, NULL, NULL, 0};
	if (openFiles(&sim, argc, argv)) {
		if (!readLoop(&sim, sim.inFile, sim.outFile)) printf("readLoop exited unexpectedly\n");
		setupLoopTeardown(&sim);
		clearList(&sim);
		closeFiles(sim.inFile, sim.outFile, argc, argv);
	}
}

/*Does the appropiate setups, loop, and teardowns*/
void setupLoopTeardown(struct simulation *sim) {
	if (GRAPHICS) graphicsSetup(sim); 
	if (TEXT) textSetup(sim);
	if (!simLoop(sim)) fprintf(sim->outFile,"simLoop exited unsuccessfully\n");
	if (GRAPHICS) graphicsTeardown(sim); 
	if (TEXT) textTeardown(sim);
}


/*Handles graphics setup*/
void graphicsSetup(struct simulation *sim) {
	if (!sa_initialize()) fprintf(sim->outFile,"Graphics failed to initalize\n");
}

/*Handles graphics teardown*/
void graphicsTeardown(struct simulation *sim) {
	simDelay(sim);
	sa_teardown();
}

/*Handles text setup*/
void textSetup(struct simulation *sim) {
	tabOutput(sim);
}

/*Handles text teardown*/
void textTeardown(struct simulation *sim) {
	if (NULL != sim->list) tabOutput(sim);
	finalOutput(sim);
}

/*The simulation loop, what else needs to be said? */
int simLoop (struct simulation* sim) {
	while (sim->list && !any(sim->list, isAtZero, NULL)) {
		sort(sim->list, comparison);
		if (GRAPHICS) graphicsSim(sim);
		if (TEXT) textSim(sim);
		iterate(sim->list, motion);
		deleteSome(&sim->list, escape, NULL, alienFree, sim->outFile);
		/*Time will increment one too many times if the last alien escapes, put in this check*/
		if (sim->list)sim->time += sim->dT;
	}
	return 1;
}

/*Calls all of the text-specific sim functions*/
void textSim(const struct simulation *sim) {
	if (newSecond(sim) || DEBUG) tabOutput(sim);
}

/*Calls all of the graphics-related sim functions*/
void graphicsSim(struct simulation *sim) {
	sa_clear();
	sim->getch = sa_getch();
	userControl(sim);
	iterate(sim->list, alienDraw);
	constGraphics(sim);
}

/*Clears the list of all remaining aliens*/
void clearList(struct simulation *sim) {
	int cleared;
	if (sim->outFile) fprintf(sim->outFile,"Clearing the attacking list...\n");
	cleared = deleteSome(&sim->list, deleteAll, NULL, alienFree, sim->outFile);
	if (sim->outFile) fprintf(sim->outFile,"    ...%d cleared\n", cleared);
}

