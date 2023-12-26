#include "CL_include"


int ConnexionClient(){
    int msqid; /*id de la messagerie*/
	long PID;   /* PID du client */
	key_t key;  /* Clé du serveur */
	dmsgbuf CONNECT_msg ={CONNECT,NULL}; /* message de connexion */
	dmsgbuf pid_msg; /*message recu depuis le serveur */
	dmsgbuf ACK_msg={ACK,NULL}; /*message d'acquisition */

	
	sprintf(CONNECT_msg.txt,"%d",getpid());
	key = ftok(CleServeur,'M');
	msqid = msgget(key,0666|IPC_CREAT);
	msgsnd(msqid, &CONNECT_msg, sizeof(CONNECT_msg.txt), 0);

    msgrcv(msqid, &pid_msg, sizeof(pid_msg.txt),PID, 0);
	printf("%s",pid_msg.txt);
	printf("message recu");
	sprintf(ACK_msg.txt,"%d",getpid());
	ACK_msg.type=ACK;
	msgsnd(msqid, &ACK_msg, sizeof(ACK_msg.txt), 0);
    return msqid;
}
void DeconnexionClient(int msqid){
    dmsgbuf DECONNECT_msg={DECONNECT,NULL};

    sprintf(DECONNECT_msg.txt,"%d",getpid());
	DECONNECT_msg.type=DECONNECT;
	msgsnd(msqid,&DECONNECT_msg,sizeof(DECONNECT_msg.txt),0);
}
