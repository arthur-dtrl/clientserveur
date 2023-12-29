#include "CL_reader.h"
#include "CL_writer.h"
#include "CL_driver.h"

int semid;
BUF *tampon;

pid_t pid_redac;
void lireDonnees(int voie,key_t sem_buf_key,key_t buf_key,int pid_redacteur) {
    pid_redac=pid_redacteur;
    if(voie==0){
        signal(SIGUSR1,lecture);
    }
    else{
        signal(SIGUSR2,lecture);
    }
    semid = semget(sem_buf_key, NVOIES, 0666);
        if (semid==-1) {
            perror("semget");
        }
    int shmid = shmget(buf_key, 2 * sizeof(BUF), 0666);
        if (shmid == -1) {
            perror("shmget");
        }
        tampon = (BUF *)shmat(shmid, NULL, 0) +1*voie;
        if (tampon == (BUF *)-1) {
            perror("shmat");
        }
    while(1);
}

void lecture(int signo){
    if (signo==SIGUSR1){
        while(semctl(semid, 0, GETVAL)<=0);
        data1[cpt]=tampon->tampon[tampon->n];
        //printf("Dernière donnée pour voie 1 a redacteur %d: %d \n",pid_redac,tampon->tampon[tampon->n]);
        kill(pid_redac,SIGUSR1);
    }
    else{
        while(semctl(semid, 1, GETVAL)<=0);
        data2[cpt]=tampon->tampon[tampon->n];
        //printf("Dernière donnée pour voie 2 a redacteur %d: %d \n",pid_redac,tampon->tampon[tampon->n]);
        kill(pid_redac,SIGUSR2);
        
    }
}
