#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

const char * get_current_time(){
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char *buffer = malloc(9 * sizeof (char));

    strftime(buffer, 9, "%H:%M:%S", timeinfo);
    return buffer;
}

int main(){
    const char *parent_time = get_current_time();
    int past_years = 0;

    printf("o pai nasceu [PID = %d], %s\n", getpid(), parent_time);

    pid_t pid[5] = {-1, -1, -1, -1, -1};
    // Para registrar os horários de nascimento
    const char *times[5];
    // Para registrar as idades
    int births[5] = {0, 0, 0, 0, 0};

    sleep(14);
    past_years = 14;

    pid[0] = fork();

    if(pid[0] < 0){
        printf("Criação falhou\n");
        return 1;
    }

    if(pid[0] == 0){
        times[0] = get_current_time();
        births[0] = past_years;
        printf("filho 1 nasceu [PID = %d] [PID do pai = %d], %s\n", getpid(), getppid(), times[0]);

        sleep(12);
        past_years += 12;

        pid[2] = fork();

        if(pid[2] < 0){
            //deu merda
            printf("Criação falhou\n");
            return 1;
        }

        if(pid[2] == 0){
            times[2] = get_current_time();
            births[2] = past_years;
            printf("neto 1 nasceu [PID = %d] [PID do pai = %d], %s\n", getpid(), getppid(), times[2]);

            sleep(12);
            past_years += 12;

            printf("neto 1 morreu [PID = %d], hora do nascimento: %s, hora da morte: %s, viveu %d anos\n", getpid(), times[2], get_current_time(), past_years - births[2]);
        }

        if(pid[2] > 0){
            sleep(18);
            past_years += 18;
            printf("filho 1 morreu [PID = %d], hora do nascimento: %s, hora da morte: %s, viveu %d anos\n", getpid(), times[0], get_current_time(), past_years - births[0]);
        }
    }
    if(pid[0] > 0){
        sleep(2);
        past_years += 2;

        pid[1] = fork();

        if(pid[1] < 0){
            //deu merda
            printf("Criação falhou\n");
            return 1;
        }
        if(pid[1] == 0){
            times[1] = get_current_time();
            births[1] = past_years;
            printf("filho 2 nasceu [PID = %d] [PID do pai = %d], %s\n", getpid(), getppid(), times[1]);

            sleep(14);
            past_years += 14;

            pid[3] = fork();

            if(pid[3] < 0){
                //deu merda
                printf("Criação falhou \n");
                return 1;
            }
            if(pid[3] == 0){
                times[3] = get_current_time();
                births[3] = past_years;
                printf("neto 2 nasceu [PID = %d] [PID do pai = %d], %s\n", getpid(), getppid(), times[3]);

                sleep(18);
                past_years += 18;

                printf("neto 2 morreu [PID = %d], hora do nascimento: %s, hora da morte: %s, viveu %d anos\n", getpid(), times[3], get_current_time(), past_years - births[3]);

            }
            if(pid[3] > 0){
                sleep(16);
                past_years += 16;

                printf("filho 2 morreu [PID = %d], hora do nascimento: %s, hora da morte: %s, viveu %d anos\n", getpid(), times[1], get_current_time(), past_years - births[1]);
            }

        }
        if(pid[1] > 0){
            sleep(44);
            past_years += 44;

            printf("pai morreu [PID = %d], hora do nascimento: %s, hora da morte: %s, viveu %d anos\n", getpid(), parent_time, get_current_time(), past_years);
        }
    }

    return 0;
}
