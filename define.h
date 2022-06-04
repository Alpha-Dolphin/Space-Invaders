/*Ben Elleman*/

#define deltaT 0.03125

#define EXIT_FAILURE 1 
#define EXIT_SUCCESS 0
#define FALSE 0
#define ERROR -1
#define TRUE 1

#define ENDSIMDELAY 4
#define UFO 3
#define BOMB 4
#define XBOUND 39.0
#define YLOWER 3.0

struct alienData{int data; int points; int type; int color; double x; double y; double vX; double vY; void* sim;};
struct simulation{double time; void *list; double basePos; int score; double dT; FILE *inFile; FILE *outFile; int getch;};

