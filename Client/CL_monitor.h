/***************************
** Fichier    CL_monitor.h       **
***************************/

int MoniteurClient(int msqid);
int ConnexionClient();
void DeconnexionClient(int msqid);
void newvalue(int signo);