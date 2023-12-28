#include "CL_include"

extern int donnees1[];
extern int donnees2[];
extern int cpt1;
extern int cpt2;

void lireDonnees(int voie,key_t sem_buf_key,key_t buf_key,int pid_redacteur);
void lecture(int signo);
