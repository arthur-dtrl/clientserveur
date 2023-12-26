/********************************************************
*	Module CL_main.c				*
*-------------------------------------------------------*
*/
#include "CL_connect.h"

#include "CL_include"


void litbuf1();
void litbuf2();

int voie;			/*variable globale (numero du canal a lire)*/

int main(int argc, char *argv[])
{	int msqid;
	msqid=ConnexionClient();
	

	signal(SIGUSR1, litbuf1);
	signal(SIGUSR2, litbuf2);

	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Projet CLIENT - SERVEUR\tTemps R�el E2i - Novembre\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
	
	DeconnexionClient(msqid);

        /* TO BE CONTINUED */
        

return 0;
}	   	   

	   	   	   
/*/////////////////////////////////////////////////////////////////////////*/
	   
void litbuf1() /* semaphore 0 */
{
	voie=0;
	signal(SIGUSR1,litbuf1);
}


/*/////////////////////////////////////////////////////////////////////////*/

void litbuf2()
{
	voie=1;	
	signal(SIGUSR2,litbuf2);
}
