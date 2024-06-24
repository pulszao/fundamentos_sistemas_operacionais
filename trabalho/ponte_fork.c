#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TAMANHO 50
#define CARROS_POR_MINUTO 90 // 30-60-90 veículos por minuto
#define TRUE 1
#define FALSE 0

struct carro {
    int id;
    int prioridade;
    int atravessou_ponte;
    pid_t pid;
};
typedef struct carro CARRO;

void ponte(CARRO *carro, sem_t *semaforo) {
    sem_wait(semaforo); // trava semaforo
    printf("PONTE 1\tCarro = %i\t Prioridade = %i\t Processo = %d\n", carro->id, carro->prioridade, getpid());
    usleep(60000000 / CARROS_POR_MINUTO); // delay para limitar velocidade de carros que passam na ponte
    sem_post(semaforo); // libera semaforo
}

void ponte2(CARRO *carro2, sem_t *semaforo) {
    sem_wait(semaforo); // trava semaforo
    printf("PONTE 2\tCarro2 = %i\t Prioridade = %i\t Processo = %d\n", carro2->id, carro2->prioridade, getpid());
    usleep(60000000 / CARROS_POR_MINUTO); // delay para limitar velocidade de carros que passam na ponte
    sem_post(semaforo); // libera semaforo
}

int main(void) {
    // Inicia gerador de números aleatórios
    srand(time(NULL));

    int shmid, shmid2;
    CARRO *carros, *carros2;

    // Criação da memória compartilhada
    shmid = shmget(IPC_PRIVATE, TAMANHO * sizeof(CARRO), IPC_CREAT | 0600);
    carros = (CARRO *)shmat(shmid, NULL, 0);

    shmid2 = shmget(IPC_PRIVATE, TAMANHO * sizeof(CARRO), IPC_CREAT | 0600);
    carros2 = (CARRO *)shmat(shmid2, NULL, 0);

    // Criação do semáforo
    sem_t *semaforo = sem_open("/semaforo_ponte", O_CREAT, 0600, 1);

    // Criando carros com suas prioridades
    for (int i = 0; i < TAMANHO; i++) {
        carros[i].id = i + 1;
        carros[i].prioridade = (rand() % 5) + 1;
        carros[i].atravessou_ponte = FALSE;

        carros2[i].id = i + 1;
        carros2[i].prioridade = (rand() % 5) + 1;
        carros2[i].atravessou_ponte = FALSE;
    }

    // Executa a função de acordo com a prioridade
    for (int prio = 1; prio <= 5; prio++) {
        for (int i = 0; i < TAMANHO; i++) {
            if (carros[i].prioridade == prio && carros[i].atravessou_ponte == FALSE) {
                carros[i].pid = fork();
                if (carros[i].pid == 0) {
                    ponte(&carros[i], semaforo);
                    carros[i].atravessou_ponte = TRUE;
                    shmdt(carros);
                }
            }
            if (carros2[i].prioridade == prio && carros2[i].atravessou_ponte == FALSE) {
                carros2[i].pid = fork();
                if (carros2[i].pid == 0) {
                    ponte2(&carros2[i], semaforo);
                    carros2[i].atravessou_ponte = TRUE;
                    shmdt(carros2);
                }
            }
        }
    }

    // Faz o wait final para verificar que todos os processos acabaram
    for (int i = 0; i < TAMANHO; i++) {
        if (carros[i].atravessou_ponte == TRUE) {
            waitpid(carros[i].pid, NULL, 0);
        }
        if (carros2[i].atravessou_ponte == TRUE) {
            waitpid(carros2[i].pid, NULL, 0);
        }
    }

    // Liberação da memória compartilhada e do semáforo
    shmdt(carros);
    shmctl(shmid, IPC_RMID, NULL);
    shmdt(carros2);
    shmctl(shmid2, IPC_RMID, NULL);

    sem_close(semaforo);
    sem_unlink("/semaforo_ponte");

    return 0;
}
