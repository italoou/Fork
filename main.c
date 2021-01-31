#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
    
    /*time*/
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    printf ("o pai nasceu [pid = %d], %s", getpid(), asctime (timeinfo));
    /*time*/

    pid_t pid[5] = {-1, -1, -1, -1, -1};
    sleep(14);
    
    pid[0] = fork();

    if(pid[0] < 0){
        //deu merda
        printf("Criação falhou \n"); 
        return 1;
    }
    if(pid[0] == 0){
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        printf("filho 1 nasceu [pid = %d] [pid do pai = %d], %s",getpid(), getppid(), asctime(timeinfo));

        sleep(12);
        
        
        pid[2] = fork();
        
        if(pid[2] < 0){
            //deu merda
            printf("Criação falhou \n"); 
            return 1;
        }
        
        if(pid[2] == 0){
            time (&rawtime);
            timeinfo = localtime (&rawtime);
            
            printf("neto 1 nasceu [pid = %d] [pid do pai = %d], %s",getpid(), getppid(), asctime(timeinfo));
            
            sleep(12);

            time (&rawtime);
            timeinfo = localtime (&rawtime);
            printf("neto 1 morreu, %s", asctime(timeinfo));
            //return 0;
        }
        
        if(pid[2] > 0){
            sleep(18);
            time (&rawtime);
            timeinfo = localtime (&rawtime);

            printf("filho 1 morreu, %s", asctime(timeinfo));
            //return 0;
        }
    }
    if(pid[0] > 0){
        sleep(2);

        pid[1] = fork();

        if(pid[1] < 0){
            //deu merda
            printf("Criação falhou \n"); 
            return 1;
        }
        if(pid[1] == 0){
            time (&rawtime);
            timeinfo = localtime (&rawtime);
            
            printf("filho 2 nasceu [pid = %d] [pid do pai = %d], %s",getpid(), getppid(), asctime(timeinfo));

            sleep(14);

            pid[3] = fork();

            if(pid[3] < 0){
                //deu merda
                printf("Criação falhou \n"); 
                return 1;
            }
            if(pid[3] == 0){
                
                time (&rawtime);
                timeinfo = localtime (&rawtime);
                
                printf("neto 2 nasceu [pid = %d] [pid do pai = %d], %s",getpid(), getppid(), asctime(timeinfo));

                sleep(18);

                time (&rawtime);
                timeinfo = localtime (&rawtime);

                printf("neto 2 morreu, %s", asctime(timeinfo));

            }
            if(pid[3] > 0){
                
                sleep(16);
                
                time (&rawtime);
                timeinfo = localtime (&rawtime);

                printf("filho 2 morreu, %s", asctime(timeinfo));
            
            }

        }
        if(pid[1] > 0){
            
            sleep(44);
            
            time (&rawtime);
            timeinfo = localtime (&rawtime);
            
            printf("pai morreu [pid= %d], %s", getpid(), asctime(timeinfo));

        }
    }

    return 0;

}

