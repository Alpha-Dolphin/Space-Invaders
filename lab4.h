/* Ben Elleman */

void clearList(struct simulation *sim) ;
void graphicsSetup(struct simulation *sim) ;
void graphicsSim(struct simulation *sim) ;
void graphicsTeardown(struct simulation *sim) ;
int main(int argc, char *argv[]) ;
void setupLoopTeardown(struct simulation *sim) ;
int simLoop (struct simulation* sim) ;
void textGraphics(int argc, char *argv[]) ;
void textSetup(struct simulation *sim) ;
void textSim(const struct simulation *sim) ;
void textTeardown(struct simulation *sim) ;
