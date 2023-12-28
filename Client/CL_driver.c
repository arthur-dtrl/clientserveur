#include "CL_writer.h"
#include "CL_include"
#include "CL_driver.h"
void Driver(){
    signal(SIGUSR1,signal_handler);
    signal(SIGUSR2,signal_handler);
    while(1);
}
void signal_handler(int signo){
    if(signo==SIGUSR1){
        for(int i =0;i<5;i++){
            printf("%d",donnees1[i]);
        }
    }
    else{
        for(int i =0;i<5;i++){
            printf("%d",donnees2[i]);
        }
    }
}
