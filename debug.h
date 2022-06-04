/*Ben Elleman*/
/*This file is mandatory so we can run 3 ways:
 * GRAPHICS has 2 modes:
 * GRAPHICS set to 1 - Supress ALL text output, draw instead
 * GRAPHICS set to 0 - Text mode, VERBOSE controls what prints.
 * TEXT has 2 modes:
 * VERBOSE set to 1 - DEBUG output
 * VERBOSE set to 0 - Only required output
 * DO NOT change TEXT or DEBUG*/

#define VERBOSE 0 /*All vs required messages*/
#define GRAPHICS 1 /*Graphics vs text*/
#define TEXT 1

#define DEBUG (VERBOSE && TEXT)
