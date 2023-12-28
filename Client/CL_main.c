/********************************************************
*	Module CL_main.c				*
*-------------------------------------------------------*
*/
#include "CL_monitor.h"
#include "CL_include"

void newvalue_1(int signo);
void newvalue_2(int signo);

int voie;			/*variable globale (numero du canal a lire)*/

int main(int argc, char *argv[])
{	
	
	int msqid=ConnexionClient();
	signal(SIGUSR1, &newvalue_1);
	signal(SIGUSR2, &newvalue_2);
	if(MoniteurClient(msqid)!=0){
		printf("Erreur");
	};
	

	
	/*printf("\n* * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Projet CLIENT - SERVEUR\tTemps R�el SEOC \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");*/
	
	DeconnexionClient(msqid);

        /* TO BE CONTINUED */
        

return 0;
}	   	   

	   	   	   
/*/////////////////////////////////////////////////////////////////////////*/
	   
void newvalue_1(int signo) /* semaphore 0 */
{	if(signo==SIGUSR1){
		printf("yo");
	}
}


/*/////////////////////////////////////////////////////////////////////////*/

void newvalue_2(int signo)
{
	if(signo==SIGUSR2){
		
		printf("yo");
	}
}

