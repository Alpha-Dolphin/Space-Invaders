/* Copyright 2022 Neil Kirby */

/* Space invaders Library code.  Not for disclosure without permission */

int sa_alien(int type, int color, double X, double Y);
int sa_base(double X);
void sa_beep();
int sa_bolt(double X);
void sa_clear();
void sa_flash();
int sa_getch();
int sa_initialize();
void sa_refresh();
void sa_score(int score);
void sa_status(const char *statstr);
void sa_teardown();
void sa_time(int milliseconds);
/* Copyright 2022 Neil Kirby */

/* Space invaders Library code.  Not for disclosure without permission */

int microsleep(unsigned int microseconds);
int millisleep(unsigned int milliseconds);
double now();
