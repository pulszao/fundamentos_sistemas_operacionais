#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAMANHO 50
#define CARROS_POR_MINUTO 60 // 30-60-90 veículos por minuto
#define TRUE 1
#define FALSE 0

struct carro {
    int id;
    int prioridade;
    int atravessou_ponte;
    pid_t pid;
};
typedef struct carro CARRO;

void ponte(CARRO *carro) {
    printf("PONTE 1\tCarro = %i\t Prioridade = %i\t Processo = %d\n", carro->id, carro->prioridade, getpid());
    usleep(60000000 / CARROS_POR_MINUTO); // delay para limitar velocidade de carros que passam na ponte
}

void ponte2(CARRO *carro2) {
    printf("PONTE 2\tCarro2 = %i\t Prioridade = %i\t Processo = %d\n", carro2->id, carro2->prioridade, getpid());
    usleep(60000000 / CARROS_POR_MINUTO); // delay para limitar velocidade de carros que passam na ponte
}

int main(void) {
    // Inicia gerador de números aleatórios
    srand(time(NULL));
    
    CARRO *carros = NULL;
    CARRO *carros2 = NULL;

    // Alocação de memória para os parâmetros
    carros = (CARRO *)malloc(TAMANHO * sizeof(CARRO));
    carros2 = (CARRO *)malloc(TAMANHO * sizeof(CARRO));

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
            if (carros[i].prioridade == prio) {
                carros[i].pid = fork();
                if (carros[i].pid == 0) {
                    ponte(&carros[i]);
                    exit(0);
                } else if (carros[i].pid > 0) {
                    carros[i].atravessou_ponte = TRUE;
                }
            }
            if (carros2[i].prioridade == prio) {
                carros2[i].pid = fork();
                if (carros2[i].pid == 0) {
                    ponte2(&carros2[i]);
                    exit(0);
                } else if (carros2[i].pid > 0) {
                    carros2[i].atravessou_ponte = TRUE;
                }
            }

            int sinaleira =  (rand() % (TAMANHO * 3)) + 1;
            if (sinaleira == 7) {
                // Faz o wait para garantir que todos os processos acabaram antes de parar
                for (int j = 0; j < TAMANHO; j++) {
                    if (carros[j].atravessou_ponte == TRUE) {
                        waitpid(carros[j].pid, NULL, 0);
                    }
                    if (carros2[j].atravessou_ponte == TRUE) {
                        waitpid(carros2[j].pid, NULL, 0);
                    }
                }

                printf("\nSinaleira Fechada!\nCarros Aguardando Sinaleira:\n");
                printf("PONTE 1\n");
                for (int j = 0; j < TAMANHO; j++) {
                    if (carros[j].atravessou_ponte == FALSE) {
                        printf("\t*(Carro = %i - Prioridade = %i)\n", carros[j].id, carros[j].prioridade);
                    }
                }
                printf("PONTE 2\n");
                for (int j = 0; j < TAMANHO; j++) {
                    if (carros2[j].atravessou_ponte == FALSE) {
                        printf("\t*(Carro = %i - Prioridade = %i)\n", carros2[j].id, carros2[j].prioridade);
                    }
                }
                sleep(10);
                printf("\nSinaleira Aberta!\n");
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

    free(carros);
    free(carros2);

    return 0;
}
