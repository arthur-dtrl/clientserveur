void RecupereDonnees(int voie){
    switch(voie){
        case 0:
            while(1){
                if(cpt1==5){
                    kill(SIGUSR1,pid_driver);
                }
            }
        case 1:
            while(1){
                if(cpt2==5){
                    kill(SIGUSR2,pid_driver);
                }
            }
    }
}
