#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>

int main(){

    pid_t pid;

    if(pid < 0){
        //deu merda
        std::cout << "Criação falhou" << std::endl; 
        return 1;
    }
    else if(pid == 0){/*processo filho*/
        std::cout << "processo filho pid = " << getpid() << ", processo pai pid = " << getppid() << std::endl;
    }
    else{/*processo pai*/
        wait(NULL);
        std::cout << "processo pai" << std::endl;
        exit(0);
    }

    return 0;
}