#include "CL_include"
#include "CL_writer.h"
int data1[5];
int data2[5];

int cpt=0;


void RecupereDonnees(int voie,int pid_driver){
    if(voie==0){
        signal(SIGUSR1,&increment);
    }
    else{
        signal(SIGUSR2,&increment);
    }
    while(1){
        //printf("%d",cpt);
        if(cpt==5){
            printf("requete driver canal %d\n",voie);
            if(voie==0){
                kill(pid_driver,SIGUSR1);
                for(int i=0;i<5;i++){
                    printf("%d",data1[i]);
                }
            }
            else{
                kill(pid_driver,SIGUSR2);
                for(int i=0;i<5;i++){
                    printf("%d",data2[i]);
                }
            }
            
            printf("\n");
            cpt=0;
        }
       fflush(stdout);
    }
}
void increment(int signo){
    cpt++;
}