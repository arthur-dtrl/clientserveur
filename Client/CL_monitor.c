#include "CL_include"
#include "CL_monitor.h"

key_t buf_key;  /* Clé du buffer */
key_t sem_buf_key;
pid_t lecteurs[2];

int ConnexionClient(){
    int msqid; /*id de la messagerie*/
    long PID;   /* PID du client */
    key_t server_key;
    dmsgbuf CONNECT_msg ={CONNECT,NULL}; /* message de connexion */
    dmsgbuf pid_msg; /*message recu depuis le serveur */
    dmsgbuf ACK_msg={ACK,NULL}; /*message d'acquisition */

    printf("\nTentative de connexion...\n");
    sprintf(CONNECT_msg.txt,"%d",getpid());
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

    if (msgsnd(msqid, &CONNECT_msg, sizeof(CONNECT_msg.txt), 0) == -1) {
        perror("Erreur msgsnd");
        return -1;
    }

    if (msgrcv(msqid, &pid_msg, sizeof(pid_msg.txt), PID, 0) == -1) {
        perror("Erreur msgrcv");
        return -1;
    }

    printf("Message reçu du serveur : %s\n", pid_msg.txt);
    buf_key=ftok(pid_msg.txt,'T');
    
    printf("Envoi de l'ACK...\n");

    sprintf(ACK_msg.txt,"%d",getpid());
    ACK_msg.type = ACK;
    if (msgsnd(msqid, &ACK_msg, sizeof(ACK_msg.txt), 0) == -1) {
        perror("Erreur lors de l'envoi du message ACK");
        return -1;
    }
	printf("Connexion au serveur réussie.\n");
    return msqid;
}

void DeconnexionClient(int msqid){
    dmsgbuf DECONNECT_msg={DECONNECT,NULL};

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
    pid_driver=fork();
    if(pid_driver==0){
        Driver();
    }
	for (int voie = 0; voie < NVOIES; voie++) {
        pid_redacteur = fork();
        if (pid_redacteur == 0) {
            printf("Création rédacteur pour voie %d \n",voie+1);
            // Processus Redacteur
            recupereDonnees(voie);
            exit(0);
        }
        pid_lecteur = fork();
        lecteurs[voie]=pid_lecteur;
        if (pid_lecteur == 0) {
            printf("Création lecteur pour voie %d \n",voie+1);
            // Processus Lecteurs
            lireDonnees(voie,sem_buf_key,buf_key,pid_redacteur);
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

	   	   	   


