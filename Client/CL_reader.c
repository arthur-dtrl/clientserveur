#include "CL_reader.h"

int donnees[5];
int semid;
BUF *tampon1;
BUF *tampon2;

void lireDonnees(int voie,key_t sem_buf_key,key_t buf_key) {
    semid = semget(sem_buf_key, NVOIES, 0666);
        if (semid==-1) {
            perror("semget");
        }
    int shmid = shmget(buf_key, 2 * sizeof(BUF), 0666);
        if (shmid == -1) {
            perror("shmget");
        }
        tampon1 = (BUF *)shmat(shmid, NULL, 0);
        if (tampon1 == (BUF *)-1) {
            perror("shmat");
        }
        tampon2 = tampon1+1;

        //signal(SIGUSR1,&litbuffer1);
        //signal(SIGUSR2,&litbuffer2);
    while(1) {
        while(semctl(semid, 0, GETVAL)<=0);
        if(voie==0){
            printf("Dernière donnée pour voie 1: %d \n",tampon1->tampon[tampon1->n]);
        }
        else{
            printf("Dernière donnée pour voie 2: %d \n",tampon2->tampon[tampon2->n]);
        }
    }
}