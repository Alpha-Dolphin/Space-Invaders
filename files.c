/*Ben Elleman*/

#include <stdio.h>

#include "define.h"
#include "debug.h"

#include "files.h"

/*Tries to open input and output files if applicable and returns its result*/
int openFiles(struct simulation *sim, int argc, char *argv[]) {
	/*I'm really tempted to turn all of this into a one line god-awful series of terniary statments, just
	 * as a challenge, but that would just be inviting an hour of unnessecarily wasted time and hard to maintain
	 * code*/
	/*I tried and it was terrible*/
	if (openInput(sim, argc, argv)) {
		if (openOutput(sim, argc, argv)) return 1;
	}
	return 0;
}

/*Function to open the input stream*/
int openInput(struct simulation *sim, int argc, char *argv[]) {
	if (argc > 1) {
		if(!(sim->inFile = fopen(argv[1], "r"))){
			printf("ERROR: Unable to open %s for input\n", argv[1]);
			return 0;
		} else {
			printf("DIAGNOSTIC: Successfully opened %s for input\n", argv[1]);
			return 1;
		}
	}
	return 0;
}

/*Function to open the output stream*/
int openOutput(struct simulation *sim, int argc, char *argv[]) {
	if (argc > 2) {
		if(!(sim->outFile = fopen(argv[2], "w"))){
			printf("ERROR: Unable to open %s for output\n", argv[2]);
			fclose(sim->inFile);
			return 0;
		} else {
			printf("DIAGNOSTIC: Successfully opened %s for output\n", argv[2]);
		}
	/*Consider defaulting stdout*/
	} else sim->outFile = stdout;
	return 1;
}

/*Closes all open files*/
void closeFiles(FILE* inFile, FILE* outFile, int argc, char* argv[]) {
	if (inFile) {
		fclose(inFile);
		printf("DIAGNOSTIC: Closed input file %s\n", argv[1]);
		if (outFile) {
			fclose(outFile);
			printf("DIAGNOSTIC: Closed output file %s\n", argv[2]);
		}
	}
}

