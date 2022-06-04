/*Ben Elleman*/
#include <stdio.h>

#include "typedef.h"

#include "invaders.h"
#include "linkedlist.h"

#include "define.h"
#include "debug.h"

#include "jumpTable.h"

#include "llfunc.h"
#include "memory.h"

/*Handles the user's input*/
void userControl(struct simulation *sim) {
	static void (*fp[256])(struct simulation*)={NULL};
	fp[32] = fp[(int) 'w'] = boltFire;
	fp[52] = fp[(int) 'a'] = left;
	fp[54] = fp[(int) 'd'] = right;
	if (sim->getch < 256 && sim->getch > -1 && fp[sim->getch]) fp[sim->getch](sim);
}

/*Shifts the base left by 1 if possible*/
void left(struct simulation *sim) {
	if (sim->basePos > -39.0) sim->basePos--;
}

/*Shifts the base right by 1 if possible*/
void right(struct simulation *sim) {
	if (sim->basePos < 39.0) sim->basePos++;
}

/*Fires bolt output and deletes all aliens hit by the bolt*/
void boltFire(struct simulation *sim) {
	sa_bolt(sim->basePos);
	sa_status("Bolt Fired");
	deleteSome(&sim->list, alienBolt, NULL, alienFree, sim->outFile);
}

