#include "CL_include"
#include "CL_writer.h"
int donnees1[5];
int donnees2[5];
int cpt1=0;
int cpt2=0;

void RecupereDonnees(int voie,int pid_driver){
    printf("yo");
    while(1){
        
        if(cpt1==5){
            printf("requete driver canal 1");
            kill(SIGUSR1,pid_driver);
            cpt1=0;
        }
        if(cpt2==5){
            printf("requete driver canal 2");
            kill(SIGUSR2,pid_driver);
            cpt2=0;
        }
        sleep(1); 
        
        }
        
         
    }
