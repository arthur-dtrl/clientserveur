#include "CL_include"
#include "CL_monitor.h"
#include "CL_writer.h"

key_t buf_key;  /* Clé du buffer */
key_t sem_buf_key;
pid_t lecteurs[2];


int ConnexionClient(){
    int msqid; /*id de la messagerie*/
    long PID;   /* PID du client */
    key_t server_key;
    dmsgbuf msg ={CONNECT,NULL}; /* message de connexion */

    printf("\nTentative de connexion...\n");
    sprintf(msg.txt,"%d",getpid());
    server_key = ftok(CleServeur,'M');
    sem_buf_key=ftok(CleServeur,'S');
    if (server_key == -1) {
        perror("Erreur ftok");
        return -1;
    }

    msqid = msgget(server_key,0666|IPC_CREAT);
    if (msqid == -1) {
        perror("Erreur msgget");
        return -1;
    }

    if (msgsnd(msqid, &msg, sizeof(msg.txt), 0) == -1) {
        perror("Erreur msgsnd");
        return -1;
    }

    if (msgrcv(msqid, &msg, sizeof(msg.txt), PID, 0) == -1) {
        perror("Erreur msgrcv");
        return -1;
    }

    printf("Message reçu du serveur : %s\n", msg.txt);
    buf_key=ftok(msg.txt,'T');
    
    printf("Envoi de l'ACK...\n");

    sprintf(msg.txt,"%d",getpid());
    msg.type = ACK;
    if (msgsnd(msqid, &msg, sizeof(msg.txt), 0) == -1) {
        perror("Erreur lors de l'envoi du message ACK");
        return -1;
    }
	printf("Connexion au serveur réussie.\n");
    return msqid;
}

void DeconnexionClient(int msqid){
    dmsgbuf DECONNECT_msg={DECONNECT,(char)NULL};

    sprintf(DECONNECT_msg.txt,"%d",getpid());
    DECONNECT_msg.type = DECONNECT;
    if (msgsnd(msqid, &DECONNECT_msg, sizeof(DECONNECT_msg.txt), 0) == -1) {
        perror("Erreur lors de la déconnexion");
    } else {
        printf("Déconnexion réussie.\n");
    }
}


void newvalue(int signo)
{   if(signo==SIGUSR1){
		printf("yo");
        kill(lecteurs[0],SIGUSR1);
    }
	else{
        printf("yo2");
        kill(lecteurs[1],SIGUSR2);
    }
}


int main(int argc, char *argv[])
{	
	pid_t pid_lecteur, pid_redacteur,pid_driver;
    
	int msqid=ConnexionClient();
    signal(SIGUSR1,&newvalue);
    signal(SIGUSR2,&newvalue);
	if (msqid < 0) {
        perror("Erreur de connexion au serveur\n");
        exit(EXIT_FAILURE);
    }
    pid_driver = fork();
    if (pid_driver == 0) {
        printf("Création driver");
        Driver();
        exit(0);
        }
	for (int voie = 0; voie < NVOIES; voie++) {
        pid_lecteur = fork();
        lecteurs[voie]=pid_lecteur;
        if (pid_lecteur == 0) {
            printf("Création lecteur pour voie %d \n",voie+1);
            // Processus Lecteurs
            lireDonnees(voie,sem_buf_key,buf_key);
            exit(0);
        }
    
        pid_redacteur = fork();
        if (pid_redacteur == 0) {
            printf("Création rédacteur pour voie %d \n",voie+1);
            // Processus Redacteur
            RecupereDonnees(voie,pid_driver);
            exit(0);
        }
    
    }

    // Attente de la fin des processus enfants
    while (wait(NULL) > 0);

    // Nettoyage des sémaphores


    // Déconnexion du client

    return 0;

	
	/*printf("\n* * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Projet CLIENT - SERVEUR\tTemps R�el SEOC \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");*/
	
	DeconnexionClient(msqid);

        /* TO BE CONTINUED */
        

return 0;
}	   	   

	   	   	   


