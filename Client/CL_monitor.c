#include "CL_include"
#include "CL_monitor.h"



key_t buf_key;  /* Clé du buffer */
key_t sem_buf_key;
#define SEM_KEY 0x1234

int MoniteurClient(int msqid){
	pid_t pid_lecteur, pid_redacteur;
	if (msqid < 0) {
        perror("Erreur de connexion au serveur\n");
        exit(EXIT_FAILURE);
    }
    
	for (int voie = 0; voie < NVOIES; voie++) {
        pid_lecteur = fork();
        if (pid_lecteur == 0) {
            printf("Création lecteur pour voie %d \n",voie+1);
            // Processus Lecteurs
            lireDonnees(voie,sem_buf_key,buf_key);
            exit(0);
            
        }
    /*
        pid_redacteur = fork();
        if (pid_redacteur == 0) {
            printf("Création rédacteur pour voie %d \n",voie+1);
            // Processus Redacteur
            //ecrireDonnees(voie);
            exit(0);
        }
    */
    }

    // Attente de la fin des processus enfants
    while (wait(NULL) > 0);

    // Nettoyage des sémaphores


    // Déconnexion du client

    return 0;
}

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

int P(int semid, int voie)
{
  struct sembuf semoper;
  semoper.sem_num = voie;
  semoper.sem_op = -1;
  semoper.sem_flg = 0;
  
  if (semop(semid, &semoper, 1) < 0)
    {
      perror("Erreur P sur le Mutex");
      return SEMerr;
    }
  
  return 0;
}

/*********************	Op�ration V
 *  ENTREE: semid = identificateur de la famille de semaphores
 *  SORTIE: neant
 *  RETOUR: 0 ou SEMerr
 */
int V(int semid, int voie)
{
  struct sembuf semoper;
  semoper.sem_num = voie;
  semoper.sem_op = 1;
  semoper.sem_flg = 0;
  
  if (semop(semid, &semoper, 1) < 0)
    {
      perror("Erreur V sur le Mutex");
      return SEMerr;
    }
  
  return 0;
}