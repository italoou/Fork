#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
    
    pid_t pid1, pid2;
    pid1 = fork();

    if(pid1 < 0){
        printf("errou");
    }
    if(pid1 == 0){
        printf("processo filho[pid =%d] [pid pai = %d]\n", getpid(), getppid());
        pid2 = fork();

        if(pid2 < 0){
            printf("errou");
        }
        if(pid2 == 0){
            printf("processo filho[pid =%d] [pid pai = %d]\n", getpid(), getppid());
            //for(;;);
        }
        if(pid2 > 0){
            //for(;;);
        }
    }
    if(pid1 > 0){
        wait(NULL);
        printf("processo filho finalizou\nprocesso pai finalizando [pid = %d]", getpid());
    }

    return 0;

}

