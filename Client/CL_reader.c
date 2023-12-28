#include "CL_reader.h"
#include "CL_writer.h"
#include "CL_driver.h"

int semid;
BUF *tampon1;
BUF *tampon2;

void lireDonnees(int voie,key_t sem_buf_key,key_t buf_key,int pid_redacteur) {
    int c=0;
    signal(SIGUSR1,lecture);
    signal(SIGUSR2,lecture);
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
    while(1);
}

void lecture(int signo){
    if (signo==SIGUSR1){
        while(semctl(semid, 0, GETVAL)<=0);
        //printf("Dernière donnée pour voie 1: %d \n",tampon1->tampon[tampon1->n]);
        donnees1[cpt1]=tampon1->tampon[tampon1->n];
        cpt1++;
    
     
    }
    else{
        while(semctl(semid, 1, GETVAL)<=0);
        //printf("Dernière donnée pour voie 2: %d \n",tampon2->tampon[tampon2->n]);
        donnees2[cpt2]=tampon2->tampon[tampon2->n];
        cpt2++;
        
    }
}
